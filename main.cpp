/*
 * main.cpp - Ultimate VTOL UAV BLDC Motor Controller for STM32F411
 *
 * Based on PID algorithm from src/PID0.c (Simulink-generated)
 * PID form: Parallel discrete PID with derivative filter
 *   Ts = 0.001s (1kHz), Forward Euler integration
 *
 * Pinout (STM32F411 Black Pill):
 *   PA8  - PWM output to ESC (TIM1 CH1, 50Hz, 1000-2000us)
 *   PA0  - Hall sensor A (interrupt, rising edge)
 *   PA1  - Hall sensor B
 *   PA2  - Hall sensor C
 *   PA9  - RC PWM input from flight controller (TIM1 CH2)
 *   PC13 - Built-in LED (status indicator)
 *   PA10 - Serial TX (USB)
 *   PA3  - Serial RX (USB)
 *
 * Commands (Serial 115200 baud):
 *   P <val>  Set proportional gain
 *   I <val>  Set integral gain
 *   D <val>  Set derivative gain
 *   N <val>  Set derivative filter coefficient
 *   S <val>  Set target speed (RPM)
 *   ARM      Arm the motor
 *   DISARM   Disarm the motor
 *   STATUS   Print current state
 *   CAL      Calibrate ESC (send max then min pulse)
 */

#include <Arduino.h>
#include <HardwareTimer.h>
#include <Servo.h>

/* ==========================================================
 *  Configuration
 * ========================================================== */

#define CONTROL_LOOP_FREQ  1000   /* Hz (1kHz = 1ms) */
#define CONTROL_PERIOD_US  1000   /* microseconds */

#define PWM_FREQ           50     /* Hz for standard ESC */
#define PWM_MIN            1000   /* us - minimum pulse */
#define PWM_MAX            2000   /* us - maximum pulse */
#define PWM_IDLE           1000   /* us - disarmed pulse */
#define PWM_ARM            1500   /* us - armed neutral */

#define HALL_POLE_PAIRS    7      /* typical BLDC for 22xx motors */
#define HALL_EVENTS_PER_REV (6 * HALL_POLE_PAIRS) /* 42 edges/rev */

#define DEFAULT_P           1.0f
#define DEFAULT_I           1.0f
#define DEFAULT_D           0.0f
#define DEFAULT_N           100.0f
#define DEFAULT_TARGET_RPM  3000.0f

#define SERIAL_BAUD         115200

#define ARM_DELAY_MS        1000  /* hold ARM for this long */
#define FAILSAFE_TIMEOUT_US 50000 /* 50ms no RC signal -> disarm */

/* Pin assignments (STM32F411 Black Pill) */
const uint8_t PIN_ESC_PWM    = PA8;
const uint8_t PIN_HALL_A     = PA0;
const uint8_t PIN_HALL_B     = PA1;
const uint8_t PIN_HALL_C     = PA2;
const uint8_t PIN_RC_INPUT   = PA9;
const uint8_t PIN_LED        = PC13;

/* ==========================================================
 *  PID State
 * ========================================================== */

typedef struct {
  /* Gains */
  float Kp;
  float Ki;
  float Kd;
  float N;

  /* Discrete states */
  float integrator;
  float filterState;

  /* Derived */
  float Ts;
  float KiTs;     /* Ki * Ts */
  float KdN;      /* Kd * N */
  float NTs;      /* N * Ts */

  /* Output limits */
  float outMin;
  float outMax;
} PIDController;

static PIDController pid = {
  DEFAULT_P, DEFAULT_I, DEFAULT_D, DEFAULT_N,
  0.0f, 0.0f,
  1.0f / CONTROL_LOOP_FREQ,
  0.0f, 0.0f, 0.0f,
  0.0f, 1.0f
};

/* ==========================================================
 *  RPM Measurement
 * ========================================================== */

static volatile float measuredRPM = 0.0f;
static volatile uint32_t lastHallEdgeUs = 0;
static volatile uint32_t hallPeriodUs = 0;

/* ==========================================================
 *  Setpoint & Output
 * ========================================================== */

static volatile float targetRPM = DEFAULT_TARGET_RPM;
static volatile float pidOutput = 0.0f;      /* normalized 0.0-1.0 */
static volatile int pulseWidth = PWM_IDLE;    /* output pulse in us */

/* ==========================================================
 *  RC Input (PWM from flight controller)
 * ========================================================== */

static volatile uint32_t rcPulseStart = 0;
static volatile float rcSetpoint = 0.0f;     /* normalized 0.0-1.0 */
static volatile uint32_t lastRcEdgeUs = 0;

/* ==========================================================
 *  Safety
 * ========================================================== */

typedef enum {
  STATE_DISARMED,
  STATE_ARMING,
  STATE_ARMED,
  STATE_FAILSAFE
} MotorState;

static MotorState motorState = STATE_DISARMED;
static uint32_t armStartMs = 0;
static bool useRcInput = false;

/* Servo object for ESC */
static Servo esc;

/* ==========================================================
 *  Function Declarations
 * ========================================================== */

void pidInit(PIDController *p, float Kp, float Ki, float Kd, float N, float Ts);
float pidStep(PIDController *p, float error);
void pidReset(PIDController *p);

void hallSensorISR(void);
void rcInputISR(void);
void controlLoopISR(void);
float readRPM(void);
uint32_t readRCPulse(void);

void processSerialCommand(const char *cmd);
void setMotorOutput(float normalized);
void calibrateESC(void);
void printStatus(void);

/* ==========================================================
 *  PID Implementation (from src/PID0.c algorithm)
 * ========================================================== */

void pidInit(PIDController *p, float Kp, float Ki, float Kd, float N, float Ts)
{
  p->Kp = Kp;
  p->Ki = Ki;
  p->Kd = Kd;
  p->N = N;
  p->Ts = Ts;
  p->KiTs = Ki * Ts;
  p->KdN = Kd * N;
  p->NTs = N * Ts;
  p->integrator = 0.0f;
  p->filterState = 0.0f;
  p->outMin = 0.0f;
  p->outMax = 1.0f;
}

float pidStep(PIDController *p, float error)
{
  /* Derivative with filter: parallel form */
  /* Same as PID0.c lines 46-66 */
  float dTerm = (p->KdN * error - p->filterState) * p->N;
  float pTerm = p->Kp * error;
  float output = pTerm + p->integrator + dTerm;

  /* Update integrator (forward Euler) */
  p->integrator += p->KiTs * error;

  /* Update filter state (forward Euler) */
  p->filterState += p->NTs * dTerm;

  /* Integrator anti-windup: clamp integrator */
  if (output > p->outMax) {
    output = p->outMax;
    p->integrator -= p->KiTs * error; /* back out the integration */
  } else if (output < p->outMin) {
    output = p->outMin;
    p->integrator -= p->KiTs * error;
  }

  return output;
}

void pidReset(PIDController *p)
{
  p->integrator = 0.0f;
  p->filterState = 0.0f;
}

/* ==========================================================
 *  RPM Measurement - Hall Sensor Interrupt
 * ========================================================== */

void hallSensorISR(void)
{
  uint32_t now = micros();
  uint32_t period = now - lastHallEdgeUs;
  
  /* Debounce: ignore edges < 50us */
  if (period < 50) {
    return;
  }

  hallPeriodUs = period;
  lastHallEdgeUs = now;

  /*
   * RPM = 60 / (period_sec * edges_per_rev)
   * RPM = 60.0 * 1e6 / (period_us * HALL_EVENTS_PER_REV)
   */
  if (period > 0) {
    measuredRPM = 60000000.0f / (period * HALL_EVENTS_PER_REV);
  }
}

/* ==========================================================
 *  RC Input Interrupt (PWM from flight controller)
 * ========================================================== */

void rcInputISR(void)
{
  uint32_t now = micros();
  if (digitalRead(PIN_RC_INPUT) == HIGH) {
    rcPulseStart = now;
  } else {
    uint32_t pulse = now - rcPulseStart;
    if (pulse > 500 && pulse < 2500) { /* valid range check */
      rcSetpoint = (pulse - 1000) / 1000.0f; /* map 1000-2000 to 0.0-1.0 */
      rcSetpoint = constrain(rcSetpoint, 0.0f, 1.0f);
      lastRcEdgeUs = now;
    }
  }
}

/* ==========================================================
 *  Control Loop (1kHz Timer Interrupt)
 * ========================================================== */

static HardwareTimer controlTimer(TIM3);

void controlLoopISR(void)
{
  static float error = 0.0f;
  float setpoint, feedback;

  if (motorState != STATE_ARMED) {
    /* Output idle pulse */
    pulseWidth = PWM_IDLE;
    esc.writeMicroseconds(pulseWidth);
    return;
  }

  /* Determine setpoint */
  if (useRcInput) {
    /* RC input: check failsafe */
    uint32_t now = micros();
    if (now - lastRcEdgeUs > FAILSAFE_TIMEOUT_US) {
      motorState = STATE_FAILSAFE;
      pulseWidth = PWM_IDLE;
      esc.writeMicroseconds(pulseWidth);
      digitalWrite(PIN_LED, HIGH); /* fast blink handled in loop */
      return;
    }
    setpoint = rcSetpoint * 10000.0f; /* map 0-1 to 0-10000 RPM range */
  } else {
    setpoint = targetRPM;
  }

  /* Read feedback */
  feedback = measuredRPM;

  /* Compute error */
  error = setpoint - feedback;

  /* Run PID */
  pidOutput = pidStep(&pid, error);

  /* Convert to PWM pulse width */
  pulseWidth = PWM_MIN + (int)(pidOutput * (PWM_MAX - PWM_MIN));
  pulseWidth = constrain(pulseWidth, PWM_MIN, PWM_MAX);

  /* Output to ESC */
  esc.writeMicroseconds(pulseWidth);
}

/* ==========================================================
 *  Motor Output Helper
 * ========================================================== */

void setMotorOutput(float normalized)
{
  pidOutput = constrain(normalized, 0.0f, 1.0f);
}

/* ==========================================================
 *  ESC Calibration
 * ========================================================== */

void calibrateESC(void)
{
  Serial.println("ESC Calibration: Sending MAX pulse (2000us)...");
  esc.writeMicroseconds(PWM_MAX);
  delay(2000);
  Serial.println("Now DISARM and power ESC. Then send CAL again...");
  Serial.println("Sending MIN pulse (1000us)...");
  esc.writeMicroseconds(PWM_MIN);
  delay(2000);
  Serial.println("ESC Calibration done. ARM to start.");
  esc.writeMicroseconds(PWM_IDLE);
}

/* ==========================================================
 *  Status Print
 * ========================================================== */

void printStatus(void)
{
  static const char *stateNames[] = {"DISARMED", "ARMING", "ARMED", "FAILSAFE"};
  Serial.println("--- VTOL Motor Controller Status ---");
  Serial.print("State:       "); Serial.println(stateNames[motorState]);
  Serial.print("Target RPM:  "); Serial.println(targetRPM);
  Serial.print("Measured RPM:"); Serial.println(measuredRPM);
  Serial.print("PID Output:  "); Serial.println(pidOutput, 4);
  Serial.print("Pulse:       "); Serial.print(pulseWidth); Serial.println(" us");
  Serial.print("P gain:      "); Serial.println(pid.Kp, 4);
  Serial.print("I gain:      "); Serial.println(pid.Ki, 4);
  Serial.print("D gain:      "); Serial.println(pid.Kd, 4);
  Serial.print("N filter:    "); Serial.println(pid.N, 2);
  if (useRcInput) {
    Serial.print("RC Setpoint: "); Serial.println(rcSetpoint, 4);
  }
  Serial.println("--------------------------------------");
}

/* ==========================================================
 *  Serial Command Parser
 * ========================================================== */

void processSerialCommand(const char *cmd)
{
  char arg[32];
  float val;

  if (sscanf(cmd, "P %f", &val) == 1) {
    pid.Kp = val;
    pid.KdN = pid.Kd * pid.N; /* recalc */
    Serial.print("P set to "); Serial.println(val);
    return;
  }
  if (sscanf(cmd, "I %f", &val) == 1) {
    pid.Ki = val;
    pid.KiTs = val * pid.Ts;
    Serial.print("I set to "); Serial.println(val);
    return;
  }
  if (sscanf(cmd, "D %f", &val) == 1) {
    pid.Kd = val;
    pid.KdN = val * pid.N;
    Serial.print("D set to "); Serial.println(val);
    return;
  }
  if (sscanf(cmd, "N %f", &val) == 1) {
    pid.N = val;
    pid.KdN = pid.Kd * val;
    pid.NTs = val * pid.Ts;
    Serial.print("N set to "); Serial.println(val);
    return;
  }
  if (sscanf(cmd, "S %f", &val) == 1) {
    targetRPM = constrain(val, 0.0f, 20000.0f);
    Serial.print("Target RPM set to "); Serial.println(targetRPM);
    return;
  }
  if (strcmp(cmd, "ARM") == 0) {
    if (motorState == STATE_DISARMED) {
      motorState = STATE_ARMING;
      armStartMs = millis();
      Serial.println("Arming... hold for 1s");
    }
    return;
  }
  if (strcmp(cmd, "DISARM") == 0) {
    motorState = STATE_DISARMED;
    pidReset(&pid);
    esc.writeMicroseconds(PWM_IDLE);
    digitalWrite(PIN_LED, LOW);
    Serial.println("Disarmed");
    return;
  }
  if (strcmp(cmd, "STATUS") == 0) {
    printStatus();
    return;
  }
  if (strcmp(cmd, "CAL") == 0) {
    calibrateESC();
    return;
  }
  if (strcmp(cmd, "RC") == 0) {
    useRcInput = !useRcInput;
    Serial.print("RC input "); Serial.println(useRcInput ? "ON" : "OFF");
    return;
  }
  if (strcmp(cmd, "RESET") == 0) {
    pidReset(&pid);
    Serial.println("PID reset");
    return;
  }

  Serial.print("Unknown: ");
  Serial.println(cmd);
  Serial.println("Commands: P <val>, I <val>, D <val>, N <val>, S <rpm>, ARM, DISARM, STATUS, CAL, RC, RESET");
}

/* ==========================================================
 *  Arduino Setup
 * ========================================================== */

void setup()
{
  /* Init PID */
  pidInit(&pid, DEFAULT_P, DEFAULT_I, DEFAULT_D, DEFAULT_N, 1.0f / CONTROL_LOOP_FREQ);

  /* Pins */
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);

  pinMode(PIN_HALL_A, INPUT_PULLUP);
  pinMode(PIN_HALL_B, INPUT_PULLUP);
  pinMode(PIN_HALL_C, INPUT_PULLUP);

  pinMode(PIN_RC_INPUT, INPUT);

  /* ESC PWM */
  esc.attach(PIN_ESC_PWM, PWM_MIN, PWM_MAX);
  esc.writeMicroseconds(PWM_IDLE);

  /* Serial */
  Serial.begin(SERIAL_BAUD);
  while (!Serial) { delay(10); }
  Serial.println("\n\nVTOL UAV Motor Controller v1.0");
  Serial.println("STM32F411 @ 1kHz PID control loop");
  Serial.println("Send 'HELP' for commands.");

  /* Attach hall sensor interrupt (HA pin, rising edge) */
  attachInterrupt(digitalPinToInterrupt(PIN_HALL_A), hallSensorISR, RISING);

  /* Attach RC input interrupt (both edges) */
  attachInterrupt(digitalPinToInterrupt(PIN_RC_INPUT), rcInputISR, CHANGE);

  /* Setup 1kHz control loop timer */
  controlTimer.setOverflow(CONTROL_LOOP_FREQ, HERTZ_FORMAT);
  controlTimer.attachInterrupt(controlLoopISR);
  controlTimer.resume();

  Serial.println("System ready. Send ARM to start.");
}

/* ==========================================================
 *  Arduino Main Loop
 * ========================================================== */

void loop()
{
  static char line[64];
  static uint8_t pos = 0;
  static uint32_t lastStatusMs = 0;
  static uint32_t lastBlinkMs = 0;
  static bool blinkState = false;

  /* Handle arming sequence */
  if (motorState == STATE_ARMING) {
    if (millis() - armStartMs >= ARM_DELAY_MS) {
      motorState = STATE_ARMED;
      esc.writeMicroseconds(PWM_ARM);
      Serial.println("Armed!");
      digitalWrite(PIN_LED, HIGH);
    }
  }

  /* Failsafe blink pattern (fast blink) */
  if (motorState == STATE_FAILSAFE) {
    if (millis() - lastBlinkMs > 100) {
      lastBlinkMs = millis();
      blinkState = !blinkState;
      digitalWrite(PIN_LED, blinkState);
    }
    /* Try to recover: if RC signal returns, go to disarmed */
    uint32_t now = micros();
    if (now - lastRcEdgeUs < FAILSAFE_TIMEOUT_US / 2) {
      motorState = STATE_DISARMED;
      digitalWrite(PIN_LED, LOW);
      Serial.println("Failsafe recovered. Re-arm to continue.");
    }
  }

  /* Print status every 2 seconds */
  if (millis() - lastStatusMs > 2000) {
    lastStatusMs = millis();
    printStatus();
  }

  /* Read serial commands */
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n' || c == '\r') {
      if (pos > 0) {
        line[pos] = '\0';
        processSerialCommand(line);
        pos = 0;
      }
    } else if (pos < sizeof(line) - 1) {
      if (c == '\b' || c == 127) {
        if (pos > 0) pos--;
      } else {
        line[pos++] = c;
      }
    }
  }
}
