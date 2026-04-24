/*
 * VOTL_UAV_MOTOR.cpp
 *
 * Code generation for model "VOTL_UAV_MOTOR".
 *
 * Model version              : 1.6
 * Simulink Coder version : 25.2 (R2025b) 28-Jul-2025
 * C++ source code generated on : Fri Apr 24 16:26:24 2026
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "VOTL_UAV_MOTOR.h"
#include "VOTL_UAV_MOTOR_private.h"
#include "rtwtypes.h"
#include "cmath"
#include <cmath>
#include <cfloat>

real_T look1_binlxpw(real_T u0, const real_T bp0[], const real_T table[],
                     uint32_T maxIndex)
{
  real_T frac;
  real_T yL_0d0;
  uint32_T iLeft;

  /* Column-major Lookup 1-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    iLeft = 0U;
    frac = (u0 - bp0[0U]) / (bp0[1U] - bp0[0U]);
  } else if (u0 < bp0[maxIndex]) {
    uint32_T bpIdx;
    uint32_T iRght;

    /* Binary Search */
    bpIdx = maxIndex >> 1U;
    iLeft = 0U;
    iRght = maxIndex;
    while (iRght - iLeft > 1U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  } else {
    iLeft = maxIndex - 1U;
    frac = (u0 - bp0[maxIndex - 1U]) / (bp0[maxIndex] - bp0[maxIndex - 1U]);
  }

  /* Column-major Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  yL_0d0 = table[iLeft];
  return (table[iLeft + 1U] - yL_0d0) * frac + yL_0d0;
}

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
void VOTL_UAV_MOTOR::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3]{
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3]{
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t { rtsiGetT(si) };

  time_T tnew { rtsiGetSolverStopTime(si) };

  time_T h { rtsiGetStepSize(si) };

  real_T *x { rtsiGetContStates(si) };

  ODE3_IntgData *id { static_cast<ODE3_IntgData *>(rtsiGetSolverData(si)) };

  real_T *y { id->y };

  real_T *f0 { id->f[0] };

  real_T *f1 { id->f[1] };

  real_T *f2 { id->f[2] };

  real_T hB[3];
  int_T i;
  int_T nXc { 1 };

  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) std::memcpy(y, x,
                     static_cast<uint_T>(nXc)*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  VOTL_UAV_MOTOR_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  this->step();
  VOTL_UAV_MOTOR_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  this->step();
  VOTL_UAV_MOTOR_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

real_T rt_remd_snf(real_T u0, real_T u1)
{
  real_T y;
  if (std::isnan(u0) || std::isnan(u1) || std::isinf(u0)) {
    y = (rtNaN);
  } else if (std::isinf(u1)) {
    y = u0;
  } else if ((u1 != 0.0) && (u1 != std::trunc(u1))) {
    real_T q;
    q = std::abs(u0 / u1);
    if (!(std::abs(q - std::floor(q + 0.5)) > DBL_EPSILON * q)) {
      y = 0.0 * u0;
    } else {
      y = std::fmod(u0, u1);
    }
  } else {
    y = std::fmod(u0, u1);
  }

  return y;
}

/* Model step function */
void VOTL_UAV_MOTOR::step()
{
  real_T rtb_FilterCoefficient;
  boolean_T tmp;
  if (rtmIsMajorTimeStep((&VOTL_UAV_MOTOR_M))) {
    /* set solver stop time */
    if (!((&VOTL_UAV_MOTOR_M)->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&(&VOTL_UAV_MOTOR_M)->solverInfo,
                            (((&VOTL_UAV_MOTOR_M)->Timing.clockTickH0 + 1) *
        (&VOTL_UAV_MOTOR_M)->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&(&VOTL_UAV_MOTOR_M)->solverInfo,
                            (((&VOTL_UAV_MOTOR_M)->Timing.clockTick0 + 1) *
        (&VOTL_UAV_MOTOR_M)->Timing.stepSize0 + (&VOTL_UAV_MOTOR_M)
        ->Timing.clockTickH0 * (&VOTL_UAV_MOTOR_M)->Timing.stepSize0 *
        4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep((&VOTL_UAV_MOTOR_M))) {
    (&VOTL_UAV_MOTOR_M)->Timing.t[0] = rtsiGetT(&(&VOTL_UAV_MOTOR_M)->solverInfo);
  }

  /* TransferFcn: '<Root>/Transfer Fcn' */
  VOTL_UAV_MOTOR_B.TransferFcn = 0.0;
  VOTL_UAV_MOTOR_B.TransferFcn += VOTL_UAV_MOTOR_P.TransferFcn_C *
    VOTL_UAV_MOTOR_X.TransferFcn_CSTATE;
  tmp = rtmIsMajorTimeStep((&VOTL_UAV_MOTOR_M));
  if (tmp) {
  }

  /* Step: '<Root>/Step' */
  if ((&VOTL_UAV_MOTOR_M)->Timing.t[0] < VOTL_UAV_MOTOR_P.Step_Time) {
    rtb_FilterCoefficient = VOTL_UAV_MOTOR_P.Step_Y0;
  } else {
    rtb_FilterCoefficient = VOTL_UAV_MOTOR_P.Step_YFinal;
  }

  /* Sum: '<Root>/Sum' incorporates:
   *  Step: '<Root>/Step'
   */
  VOTL_UAV_MOTOR_B.Sum = rtb_FilterCoefficient - VOTL_UAV_MOTOR_B.TransferFcn;
  if (tmp) {
    /* Outputs for Atomic SubSystem: '<Root>/Subsystem' */
    /* Gain: '<S41>/Filter Coefficient' incorporates:
     *  DiscreteIntegrator: '<S33>/Filter'
     *  Gain: '<S31>/Derivative Gain'
     *  Sum: '<S33>/SumD'
     */
    rtb_FilterCoefficient = (VOTL_UAV_MOTOR_P.PIDController_D *
      VOTL_UAV_MOTOR_B.Sum - VOTL_UAV_MOTOR_DW.Filter_DSTATE) *
      VOTL_UAV_MOTOR_P.PIDController_N;

    /* Sum: '<S47>/Sum' incorporates:
     *  DiscreteIntegrator: '<S38>/Integrator'
     *  Gain: '<S43>/Proportional Gain'
     */
    VOTL_UAV_MOTOR_B.Sum_m = (VOTL_UAV_MOTOR_P.PIDController_P *
      VOTL_UAV_MOTOR_B.Sum + VOTL_UAV_MOTOR_DW.Integrator_DSTATE) +
      rtb_FilterCoefficient;

    /* Update for DiscreteIntegrator: '<S33>/Filter' */
    VOTL_UAV_MOTOR_DW.Filter_DSTATE += VOTL_UAV_MOTOR_P.Filter_gainval *
      rtb_FilterCoefficient;

    /* Update for DiscreteIntegrator: '<S38>/Integrator' incorporates:
     *  Gain: '<S35>/Integral Gain'
     */
    VOTL_UAV_MOTOR_DW.Integrator_DSTATE += VOTL_UAV_MOTOR_P.PIDController_I *
      VOTL_UAV_MOTOR_B.Sum * VOTL_UAV_MOTOR_P.Integrator_gainval;

    /* End of Outputs for SubSystem: '<Root>/Subsystem' */

    /* Saturate: '<Root>/Saturation' */
    if (VOTL_UAV_MOTOR_B.Sum_m > VOTL_UAV_MOTOR_P.Saturation_UpperSat) {
      /* Saturate: '<Root>/Saturation' */
      VOTL_UAV_MOTOR_B.Saturation = VOTL_UAV_MOTOR_P.Saturation_UpperSat;
    } else if (VOTL_UAV_MOTOR_B.Sum_m < VOTL_UAV_MOTOR_P.Saturation_LowerSat) {
      /* Saturate: '<Root>/Saturation' */
      VOTL_UAV_MOTOR_B.Saturation = VOTL_UAV_MOTOR_P.Saturation_LowerSat;
    } else {
      /* Saturate: '<Root>/Saturation' */
      VOTL_UAV_MOTOR_B.Saturation = VOTL_UAV_MOTOR_B.Sum_m;
    }

    /* End of Saturate: '<Root>/Saturation' */
  }

  /* RelationalOperator: '<Root>/Relational Operator' incorporates:
   *  Clock: '<S1>/Clock'
   *  Constant: '<S1>/Constant'
   *  Lookup_n-D: '<S1>/Look-Up Table1'
   *  Math: '<S1>/Math Function'
   *  S-Function (sfun_tstart): '<S1>/startTime'
   *  Sum: '<S1>/Sum'
   */
  VOTL_UAV_MOTOR_B.RelationalOperator = (VOTL_UAV_MOTOR_B.Saturation >
    look1_binlxpw(rt_remd_snf((&VOTL_UAV_MOTOR_M)->Timing.t[0] - (0.0),
    VOTL_UAV_MOTOR_P.Constant_Value), VOTL_UAV_MOTOR_P.LookUpTable1_bp01Data,
                  VOTL_UAV_MOTOR_P.RepeatingSequence_rep_seq_y, 1U));
  if (tmp) {
  }

  if (rtmIsMajorTimeStep((&VOTL_UAV_MOTOR_M))) {
    /* Matfile logging */
    rt_UpdateTXYLogVars((&VOTL_UAV_MOTOR_M)->rtwLogInfo, ((&VOTL_UAV_MOTOR_M)
      ->Timing.t));
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep((&VOTL_UAV_MOTOR_M))) {
    /* signal main to stop simulation */
    {                                  /* Sample time: [0.0s, 0.0s] */
      if ((rtmGetTFinal((&VOTL_UAV_MOTOR_M))!=-1) &&
          !((rtmGetTFinal((&VOTL_UAV_MOTOR_M))-((((&VOTL_UAV_MOTOR_M)
               ->Timing.clockTick1+(&VOTL_UAV_MOTOR_M)->Timing.clockTickH1*
               4294967296.0)) * 0.001)) > ((((&VOTL_UAV_MOTOR_M)
              ->Timing.clockTick1+(&VOTL_UAV_MOTOR_M)->Timing.clockTickH1*
              4294967296.0)) * 0.001) * (DBL_EPSILON))) {
        rtmSetErrorStatus((&VOTL_UAV_MOTOR_M), "Simulation finished");
      }
    }

    rt_ertODEUpdateContinuousStates(&(&VOTL_UAV_MOTOR_M)->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++(&VOTL_UAV_MOTOR_M)->Timing.clockTick0)) {
      ++(&VOTL_UAV_MOTOR_M)->Timing.clockTickH0;
    }

    (&VOTL_UAV_MOTOR_M)->Timing.t[0] = rtsiGetSolverStopTime(&(&VOTL_UAV_MOTOR_M)
      ->solverInfo);

    {
      /* Update absolute timer for sample time: [0.001s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.001, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      (&VOTL_UAV_MOTOR_M)->Timing.clockTick1++;
      if (!(&VOTL_UAV_MOTOR_M)->Timing.clockTick1) {
        (&VOTL_UAV_MOTOR_M)->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void VOTL_UAV_MOTOR::VOTL_UAV_MOTOR_derivatives()
{
  XDot_VOTL_UAV_MOTOR_T *_rtXdot;
  _rtXdot = ((XDot_VOTL_UAV_MOTOR_T *) (&VOTL_UAV_MOTOR_M)->derivs);

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE = VOTL_UAV_MOTOR_P.TransferFcn_A *
    VOTL_UAV_MOTOR_X.TransferFcn_CSTATE;
  _rtXdot->TransferFcn_CSTATE += VOTL_UAV_MOTOR_B.Sum_m;
}

/* Model initialize function */
void VOTL_UAV_MOTOR::initialize()
{
  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&(&VOTL_UAV_MOTOR_M)->solverInfo, &(&VOTL_UAV_MOTOR_M
                          )->Timing.simTimeStep);
    rtsiSetTPtr(&(&VOTL_UAV_MOTOR_M)->solverInfo, &rtmGetTPtr((&VOTL_UAV_MOTOR_M)));
    rtsiSetStepSizePtr(&(&VOTL_UAV_MOTOR_M)->solverInfo, &(&VOTL_UAV_MOTOR_M)
                       ->Timing.stepSize0);
    rtsiSetdXPtr(&(&VOTL_UAV_MOTOR_M)->solverInfo, &(&VOTL_UAV_MOTOR_M)->derivs);
    rtsiSetContStatesPtr(&(&VOTL_UAV_MOTOR_M)->solverInfo, (real_T **)
                         &(&VOTL_UAV_MOTOR_M)->contStates);
    rtsiSetNumContStatesPtr(&(&VOTL_UAV_MOTOR_M)->solverInfo,
      &(&VOTL_UAV_MOTOR_M)->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&VOTL_UAV_MOTOR_M)->solverInfo,
      &(&VOTL_UAV_MOTOR_M)->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&VOTL_UAV_MOTOR_M)->solverInfo,
      &(&VOTL_UAV_MOTOR_M)->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&VOTL_UAV_MOTOR_M)->solverInfo,
      &(&VOTL_UAV_MOTOR_M)->periodicContStateRanges);
    rtsiSetContStateDisabledPtr(&(&VOTL_UAV_MOTOR_M)->solverInfo, (boolean_T**)
      &(&VOTL_UAV_MOTOR_M)->contStateDisabled);
    rtsiSetErrorStatusPtr(&(&VOTL_UAV_MOTOR_M)->solverInfo, (&rtmGetErrorStatus
      ((&VOTL_UAV_MOTOR_M))));
    rtsiSetRTModelPtr(&(&VOTL_UAV_MOTOR_M)->solverInfo, (&VOTL_UAV_MOTOR_M));
  }

  rtsiSetSimTimeStep(&(&VOTL_UAV_MOTOR_M)->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&(&VOTL_UAV_MOTOR_M)->solverInfo, false);
  rtsiSetIsContModeFrozen(&(&VOTL_UAV_MOTOR_M)->solverInfo, false);
  (&VOTL_UAV_MOTOR_M)->intgData.y = (&VOTL_UAV_MOTOR_M)->odeY;
  (&VOTL_UAV_MOTOR_M)->intgData.f[0] = (&VOTL_UAV_MOTOR_M)->odeF[0];
  (&VOTL_UAV_MOTOR_M)->intgData.f[1] = (&VOTL_UAV_MOTOR_M)->odeF[1];
  (&VOTL_UAV_MOTOR_M)->intgData.f[2] = (&VOTL_UAV_MOTOR_M)->odeF[2];
  (&VOTL_UAV_MOTOR_M)->contStates = ((X_VOTL_UAV_MOTOR_T *) &VOTL_UAV_MOTOR_X);
  (&VOTL_UAV_MOTOR_M)->contStateDisabled = ((XDis_VOTL_UAV_MOTOR_T *)
    &VOTL_UAV_MOTOR_XDis);
  (&VOTL_UAV_MOTOR_M)->Timing.tStart = (0.0);
  rtsiSetSolverData(&(&VOTL_UAV_MOTOR_M)->solverInfo, static_cast<void *>
                    (&(&VOTL_UAV_MOTOR_M)->intgData));
  rtsiSetSolverName(&(&VOTL_UAV_MOTOR_M)->solverInfo,"ode3");
  rtmSetTPtr((&VOTL_UAV_MOTOR_M), &(&VOTL_UAV_MOTOR_M)->Timing.tArray[0]);
  rtmSetTFinal((&VOTL_UAV_MOTOR_M), 0.05);
  (&VOTL_UAV_MOTOR_M)->Timing.stepSize0 = 0.001;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = (nullptr);
    (&VOTL_UAV_MOTOR_M)->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo((&VOTL_UAV_MOTOR_M)->rtwLogInfo, (nullptr));
    rtliSetLogXSignalPtrs((&VOTL_UAV_MOTOR_M)->rtwLogInfo, (nullptr));
    rtliSetLogT((&VOTL_UAV_MOTOR_M)->rtwLogInfo, "tout");
    rtliSetLogX((&VOTL_UAV_MOTOR_M)->rtwLogInfo, "");
    rtliSetLogXFinal((&VOTL_UAV_MOTOR_M)->rtwLogInfo, "");
    rtliSetLogVarNameModifier((&VOTL_UAV_MOTOR_M)->rtwLogInfo, "rt_");
    rtliSetLogFormat((&VOTL_UAV_MOTOR_M)->rtwLogInfo, 4);
    rtliSetLogMaxRows((&VOTL_UAV_MOTOR_M)->rtwLogInfo, 0);
    rtliSetLogDecimation((&VOTL_UAV_MOTOR_M)->rtwLogInfo, 1);
    rtliSetLogY((&VOTL_UAV_MOTOR_M)->rtwLogInfo, "");
    rtliSetLogYSignalInfo((&VOTL_UAV_MOTOR_M)->rtwLogInfo, (nullptr));
    rtliSetLogYSignalPtrs((&VOTL_UAV_MOTOR_M)->rtwLogInfo, (nullptr));
  }

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime((&VOTL_UAV_MOTOR_M)->rtwLogInfo, 0.0,
    rtmGetTFinal((&VOTL_UAV_MOTOR_M)), (&VOTL_UAV_MOTOR_M)->Timing.stepSize0,
    (&rtmGetErrorStatus((&VOTL_UAV_MOTOR_M))));

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn' */
  VOTL_UAV_MOTOR_X.TransferFcn_CSTATE = 0.0;

  /* SystemInitialize for Atomic SubSystem: '<Root>/Subsystem' */
  /* InitializeConditions for DiscreteIntegrator: '<S33>/Filter' */
  VOTL_UAV_MOTOR_DW.Filter_DSTATE =
    VOTL_UAV_MOTOR_P.PIDController_InitialConditionF;

  /* InitializeConditions for DiscreteIntegrator: '<S38>/Integrator' */
  VOTL_UAV_MOTOR_DW.Integrator_DSTATE =
    VOTL_UAV_MOTOR_P.PIDController_InitialConditio_c;

  /* End of SystemInitialize for SubSystem: '<Root>/Subsystem' */
}

/* Model terminate function */
void VOTL_UAV_MOTOR::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
VOTL_UAV_MOTOR::VOTL_UAV_MOTOR() :
  VOTL_UAV_MOTOR_B(),
  VOTL_UAV_MOTOR_DW(),
  VOTL_UAV_MOTOR_X(),
  VOTL_UAV_MOTOR_XDis(),
  VOTL_UAV_MOTOR_M()
{
  /* Currently there is no constructor body generated.*/
}

/* Destructor */
/* Currently there is no destructor body generated.*/
VOTL_UAV_MOTOR::~VOTL_UAV_MOTOR() = default;

/* Real-Time Model get method */
RT_MODEL_VOTL_UAV_MOTOR_T * VOTL_UAV_MOTOR::getRTM()
{
  return (&VOTL_UAV_MOTOR_M);
}
