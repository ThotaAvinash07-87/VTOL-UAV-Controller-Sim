/*
 * VOTL_UAV_MOTOR.h
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

#ifndef VOTL_UAV_MOTOR_h_
#define VOTL_UAV_MOTOR_h_
#include <cmath>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#include "rt_nonfinite.h"
#include "VOTL_UAV_MOTOR_types.h"

extern "C"
{

#include "rtGetNaN.h"

}

#include <cfloat>
#include <cstring>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetContStateDisabled
#define rtmGetContStateDisabled(rtm)   ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
#define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
#define rtmGetContStates(rtm)          ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
#define rtmSetContStates(rtm, val)     ((rtm)->contStates = (val))
#endif

#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
#define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
#define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetIntgData
#define rtmGetIntgData(rtm)            ((rtm)->intgData)
#endif

#ifndef rtmSetIntgData
#define rtmSetIntgData(rtm, val)       ((rtm)->intgData = (val))
#endif

#ifndef rtmGetOdeF
#define rtmGetOdeF(rtm)                ((rtm)->odeF)
#endif

#ifndef rtmSetOdeF
#define rtmSetOdeF(rtm, val)           ((rtm)->odeF = (val))
#endif

#ifndef rtmGetOdeY
#define rtmGetOdeY(rtm)                ((rtm)->odeY)
#endif

#ifndef rtmSetOdeY
#define rtmSetOdeY(rtm, val)           ((rtm)->odeY = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
#define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
#define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
#define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
#define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetRTWLogInfo
#define rtmGetRTWLogInfo(rtm)          ((rtm)->rtwLogInfo)
#endif

#ifndef rtmGetZCCacheNeedsReset
#define rtmGetZCCacheNeedsReset(rtm)   ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
#define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
#define rtmGetdX(rtm)                  ((rtm)->derivs)
#endif

#ifndef rtmSetdX
#define rtmSetdX(rtm, val)             ((rtm)->derivs = (val))
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

#ifndef rtmGetTStart
#define rtmGetTStart(rtm)              ((rtm)->Timing.tStart)
#endif

/* Block signals (default storage) */
struct B_VOTL_UAV_MOTOR_T {
  real_T TransferFcn;                  /* '<Root>/Transfer Fcn' */
  real_T Sum;                          /* '<Root>/Sum' */
  real_T Saturation;                   /* '<Root>/Saturation' */
  real_T Sum_m;                        /* '<S47>/Sum' */
  boolean_T RelationalOperator;        /* '<Root>/Relational Operator' */
};

/* Block states (default storage) for system '<Root>' */
struct DW_VOTL_UAV_MOTOR_T {
  real_T Filter_DSTATE;                /* '<S33>/Filter' */
  real_T Integrator_DSTATE;            /* '<S38>/Integrator' */
};

/* Continuous states (default storage) */
struct X_VOTL_UAV_MOTOR_T {
  real_T TransferFcn_CSTATE;           /* '<Root>/Transfer Fcn' */
};

/* State derivatives (default storage) */
struct XDot_VOTL_UAV_MOTOR_T {
  real_T TransferFcn_CSTATE;           /* '<Root>/Transfer Fcn' */
};

/* State disabled  */
struct XDis_VOTL_UAV_MOTOR_T {
  boolean_T TransferFcn_CSTATE;        /* '<Root>/Transfer Fcn' */
};

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
struct ODE3_IntgData {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
};

#endif

/* Parameters (default storage) */
struct P_VOTL_UAV_MOTOR_T_ {
  real_T PIDController_D;              /* Mask Parameter: PIDController_D
                                        * Referenced by: '<S31>/Derivative Gain'
                                        */
  real_T PIDController_I;              /* Mask Parameter: PIDController_I
                                        * Referenced by: '<S35>/Integral Gain'
                                        */
  real_T PIDController_InitialConditionF;
                              /* Mask Parameter: PIDController_InitialConditionF
                               * Referenced by: '<S33>/Filter'
                               */
  real_T PIDController_InitialConditio_c;
                              /* Mask Parameter: PIDController_InitialConditio_c
                               * Referenced by: '<S38>/Integrator'
                               */
  real_T PIDController_N;              /* Mask Parameter: PIDController_N
                                        * Referenced by: '<S41>/Filter Coefficient'
                                        */
  real_T PIDController_P;              /* Mask Parameter: PIDController_P
                                        * Referenced by: '<S43>/Proportional Gain'
                                        */
  real_T RepeatingSequence_rep_seq_y[2];
                                  /* Mask Parameter: RepeatingSequence_rep_seq_y
                                   * Referenced by: '<S1>/Look-Up Table1'
                                   */
  real_T Filter_gainval;               /* Computed Parameter: Filter_gainval
                                        * Referenced by: '<S33>/Filter'
                                        */
  real_T Integrator_gainval;           /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S38>/Integrator'
                                        */
  real_T TransferFcn_A;                /* Computed Parameter: TransferFcn_A
                                        * Referenced by: '<Root>/Transfer Fcn'
                                        */
  real_T TransferFcn_C;                /* Computed Parameter: TransferFcn_C
                                        * Referenced by: '<Root>/Transfer Fcn'
                                        */
  real_T Step_Time;                    /* Expression: 0
                                        * Referenced by: '<Root>/Step'
                                        */
  real_T Step_Y0;                      /* Expression: 0
                                        * Referenced by: '<Root>/Step'
                                        */
  real_T Step_YFinal;                  /* Expression: 500
                                        * Referenced by: '<Root>/Step'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 1000
                                        * Referenced by: '<Root>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: 0
                                        * Referenced by: '<Root>/Saturation'
                                        */
  real_T Constant_Value;               /* Expression: period
                                        * Referenced by: '<S1>/Constant'
                                        */
  real_T LookUpTable1_bp01Data[2];     /* Expression: rep_seq_t - min(rep_seq_t)
                                        * Referenced by: '<S1>/Look-Up Table1'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_VOTL_UAV_MOTOR_T {
  const char_T *errorStatus;
  RTWLogInfo *rtwLogInfo;
  RTWSolverInfo solverInfo;
  X_VOTL_UAV_MOTOR_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis_VOTL_UAV_MOTOR_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[1];
  real_T odeF[3][1];
  ODE3_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    time_T tStart;
    time_T tFinal;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Class declaration for model VOTL_UAV_MOTOR */
class VOTL_UAV_MOTOR final
{
  /* public data and function members */
 public:
  /* Copy Constructor */
  VOTL_UAV_MOTOR(VOTL_UAV_MOTOR const&) = delete;

  /* Assignment Operator */
  VOTL_UAV_MOTOR& operator= (VOTL_UAV_MOTOR const&) & = delete;

  /* Move Constructor */
  VOTL_UAV_MOTOR(VOTL_UAV_MOTOR &&) = delete;

  /* Move Assignment Operator */
  VOTL_UAV_MOTOR& operator= (VOTL_UAV_MOTOR &&) = delete;

  /* Real-Time Model get method */
  RT_MODEL_VOTL_UAV_MOTOR_T * getRTM();

  /* model start function */
  void start();

  /* Initial conditions function */
  void initialize();

  /* model step function */
  void step();

  /* model terminate function */
  static void terminate();

  /* Constructor */
  VOTL_UAV_MOTOR();

  /* Destructor */
  ~VOTL_UAV_MOTOR();

  /* private data and function members */
 private:
  /* Block signals */
  B_VOTL_UAV_MOTOR_T VOTL_UAV_MOTOR_B;

  /* Block states */
  DW_VOTL_UAV_MOTOR_T VOTL_UAV_MOTOR_DW;

  /* Tunable parameters */
  static P_VOTL_UAV_MOTOR_T VOTL_UAV_MOTOR_P;

  /* Block continuous states */
  X_VOTL_UAV_MOTOR_T VOTL_UAV_MOTOR_X;

  /* Block Continuous state disabled vector */
  XDis_VOTL_UAV_MOTOR_T VOTL_UAV_MOTOR_XDis;

  /* Global mass matrix */

  /* Continuous states update member function*/
  void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si );

  /* Derivatives member function */
  void VOTL_UAV_MOTOR_derivatives();

  /* Real-Time Model */
  RT_MODEL_VOTL_UAV_MOTOR_T VOTL_UAV_MOTOR_M;
};

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'VOTL_UAV_MOTOR'
 * '<S1>'   : 'VOTL_UAV_MOTOR/Repeating Sequence'
 * '<S2>'   : 'VOTL_UAV_MOTOR/Subsystem'
 * '<S3>'   : 'VOTL_UAV_MOTOR/Subsystem/PID Controller'
 * '<S4>'   : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/Anti-windup'
 * '<S5>'   : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/D Gain'
 * '<S6>'   : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/External Derivative'
 * '<S7>'   : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/Filter'
 * '<S8>'   : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/Filter ICs'
 * '<S9>'   : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/I Gain'
 * '<S10>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/Ideal P Gain'
 * '<S11>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/Ideal P Gain Fdbk'
 * '<S12>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/Integrator'
 * '<S13>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/Integrator ICs'
 * '<S14>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/N Copy'
 * '<S15>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/N Gain'
 * '<S16>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/P Copy'
 * '<S17>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/Parallel P Gain'
 * '<S18>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/Reset Signal'
 * '<S19>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/Saturation'
 * '<S20>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/Saturation Fdbk'
 * '<S21>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/Sum'
 * '<S22>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/Sum Fdbk'
 * '<S23>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/Tracking Mode'
 * '<S24>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/Tracking Mode Sum'
 * '<S25>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/Tsamp - Integral'
 * '<S26>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/Tsamp - Ngain'
 * '<S27>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/postSat Signal'
 * '<S28>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/preInt Signal'
 * '<S29>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/preSat Signal'
 * '<S30>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/Anti-windup/Passthrough'
 * '<S31>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/D Gain/Internal Parameters'
 * '<S32>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/External Derivative/Error'
 * '<S33>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S34>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S35>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/I Gain/Internal Parameters'
 * '<S36>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/Ideal P Gain/Passthrough'
 * '<S37>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S38>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/Integrator/Discrete'
 * '<S39>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/Integrator ICs/Internal IC'
 * '<S40>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/N Copy/Disabled'
 * '<S41>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/N Gain/Internal Parameters'
 * '<S42>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/P Copy/Disabled'
 * '<S43>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S44>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/Reset Signal/Disabled'
 * '<S45>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/Saturation/Passthrough'
 * '<S46>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/Saturation Fdbk/Disabled'
 * '<S47>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/Sum/Sum_PID'
 * '<S48>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/Sum Fdbk/Disabled'
 * '<S49>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/Tracking Mode/Disabled'
 * '<S50>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S51>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S52>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S53>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/postSat Signal/Forward_Path'
 * '<S54>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/preInt Signal/Internal PreInt'
 * '<S55>'  : 'VOTL_UAV_MOTOR/Subsystem/PID Controller/preSat Signal/Forward_Path'
 */
#endif                                 /* VOTL_UAV_MOTOR_h_ */
