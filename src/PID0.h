/*
 * PID0.h
 *
 * Code generation for model "PID0".
 *
 * Model version              : 1.6
 * Simulink Coder version : 25.2 (R2025b) 28-Jul-2025
 * C source code generated on : Tue Apr 21 09:47:39 2026
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef PID0_h_
#define PID0_h_
#ifndef PID0_COMMON_INCLUDES_
#define PID0_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#include "rt_nonfinite.h"
#include "math.h"
#endif                                 /* PID0_COMMON_INCLUDES_ */

#include "PID0_types.h"
#include <float.h>
#include <string.h>
#include <stddef.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWLogInfo
#define rtmGetRTWLogInfo(rtm)          ((rtm)->rtwLogInfo)
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
#define rtmGetT(rtm)                   ((rtm)->Timing.taskTime0)
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                (&(rtm)->Timing.taskTime0)
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T Integrator_DSTATE;            /* '<S36>/Integrator' */
  real_T Filter_DSTATE;                /* '<S31>/Filter' */
} DW_PID0_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T u;                            /* '<Root>/u' */
} ExtU_PID0_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T y;                            /* '<Root>/y' */
} ExtY_PID0_T;

/* Parameters (default storage) */
struct P_PID0_T_ {
  real_T PIDController_D;              /* Mask Parameter: PIDController_D
                                        * Referenced by: '<S29>/Derivative Gain'
                                        */
  real_T PIDController_I;              /* Mask Parameter: PIDController_I
                                        * Referenced by: '<S33>/Integral Gain'
                                        */
  real_T PIDController_InitialConditionF;
                              /* Mask Parameter: PIDController_InitialConditionF
                               * Referenced by: '<S31>/Filter'
                               */
  real_T PIDController_InitialConditio_c;
                              /* Mask Parameter: PIDController_InitialConditio_c
                               * Referenced by: '<S36>/Integrator'
                               */
  real_T PIDController_N;              /* Mask Parameter: PIDController_N
                                        * Referenced by: '<S39>/Filter Coefficient'
                                        */
  real_T PIDController_P;              /* Mask Parameter: PIDController_P
                                        * Referenced by: '<S41>/Proportional Gain'
                                        */
  real_T Integrator_gainval;           /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S36>/Integrator'
                                        */
  real_T Filter_gainval;               /* Computed Parameter: Filter_gainval
                                        * Referenced by: '<S31>/Filter'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_PID0_T {
  const char_T *errorStatus;
  RTWLogInfo *rtwLogInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T taskTime0;
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    time_T tFinal;
    boolean_T stopRequestedFlag;
  } Timing;
};

/* Block parameters (default storage) */
extern P_PID0_T PID0_P;

/* Block states (default storage) */
extern DW_PID0_T PID0_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_PID0_T PID0_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_PID0_T PID0_Y;

/* Model entry point functions */
extern void PID0_initialize(void);
extern void PID0_step(void);
extern void PID0_terminate(void);

/* Real-time Model object */
extern RT_MODEL_PID0_T *const PID0_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('VOTL_UAV_MOTOR/PID Controller')    - opens subsystem VOTL_UAV_MOTOR/PID Controller
 * hilite_system('VOTL_UAV_MOTOR/PID Controller/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'VOTL_UAV_MOTOR'
 * '<S1>'   : 'VOTL_UAV_MOTOR/PID Controller'
 * '<S2>'   : 'VOTL_UAV_MOTOR/PID Controller/Anti-windup'
 * '<S3>'   : 'VOTL_UAV_MOTOR/PID Controller/D Gain'
 * '<S4>'   : 'VOTL_UAV_MOTOR/PID Controller/External Derivative'
 * '<S5>'   : 'VOTL_UAV_MOTOR/PID Controller/Filter'
 * '<S6>'   : 'VOTL_UAV_MOTOR/PID Controller/Filter ICs'
 * '<S7>'   : 'VOTL_UAV_MOTOR/PID Controller/I Gain'
 * '<S8>'   : 'VOTL_UAV_MOTOR/PID Controller/Ideal P Gain'
 * '<S9>'   : 'VOTL_UAV_MOTOR/PID Controller/Ideal P Gain Fdbk'
 * '<S10>'  : 'VOTL_UAV_MOTOR/PID Controller/Integrator'
 * '<S11>'  : 'VOTL_UAV_MOTOR/PID Controller/Integrator ICs'
 * '<S12>'  : 'VOTL_UAV_MOTOR/PID Controller/N Copy'
 * '<S13>'  : 'VOTL_UAV_MOTOR/PID Controller/N Gain'
 * '<S14>'  : 'VOTL_UAV_MOTOR/PID Controller/P Copy'
 * '<S15>'  : 'VOTL_UAV_MOTOR/PID Controller/Parallel P Gain'
 * '<S16>'  : 'VOTL_UAV_MOTOR/PID Controller/Reset Signal'
 * '<S17>'  : 'VOTL_UAV_MOTOR/PID Controller/Saturation'
 * '<S18>'  : 'VOTL_UAV_MOTOR/PID Controller/Saturation Fdbk'
 * '<S19>'  : 'VOTL_UAV_MOTOR/PID Controller/Sum'
 * '<S20>'  : 'VOTL_UAV_MOTOR/PID Controller/Sum Fdbk'
 * '<S21>'  : 'VOTL_UAV_MOTOR/PID Controller/Tracking Mode'
 * '<S22>'  : 'VOTL_UAV_MOTOR/PID Controller/Tracking Mode Sum'
 * '<S23>'  : 'VOTL_UAV_MOTOR/PID Controller/Tsamp - Integral'
 * '<S24>'  : 'VOTL_UAV_MOTOR/PID Controller/Tsamp - Ngain'
 * '<S25>'  : 'VOTL_UAV_MOTOR/PID Controller/postSat Signal'
 * '<S26>'  : 'VOTL_UAV_MOTOR/PID Controller/preInt Signal'
 * '<S27>'  : 'VOTL_UAV_MOTOR/PID Controller/preSat Signal'
 * '<S28>'  : 'VOTL_UAV_MOTOR/PID Controller/Anti-windup/Passthrough'
 * '<S29>'  : 'VOTL_UAV_MOTOR/PID Controller/D Gain/Internal Parameters'
 * '<S30>'  : 'VOTL_UAV_MOTOR/PID Controller/External Derivative/Error'
 * '<S31>'  : 'VOTL_UAV_MOTOR/PID Controller/Filter/Disc. Forward Euler Filter'
 * '<S32>'  : 'VOTL_UAV_MOTOR/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S33>'  : 'VOTL_UAV_MOTOR/PID Controller/I Gain/Internal Parameters'
 * '<S34>'  : 'VOTL_UAV_MOTOR/PID Controller/Ideal P Gain/Passthrough'
 * '<S35>'  : 'VOTL_UAV_MOTOR/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S36>'  : 'VOTL_UAV_MOTOR/PID Controller/Integrator/Discrete'
 * '<S37>'  : 'VOTL_UAV_MOTOR/PID Controller/Integrator ICs/Internal IC'
 * '<S38>'  : 'VOTL_UAV_MOTOR/PID Controller/N Copy/Disabled'
 * '<S39>'  : 'VOTL_UAV_MOTOR/PID Controller/N Gain/Internal Parameters'
 * '<S40>'  : 'VOTL_UAV_MOTOR/PID Controller/P Copy/Disabled'
 * '<S41>'  : 'VOTL_UAV_MOTOR/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S42>'  : 'VOTL_UAV_MOTOR/PID Controller/Reset Signal/Disabled'
 * '<S43>'  : 'VOTL_UAV_MOTOR/PID Controller/Saturation/Passthrough'
 * '<S44>'  : 'VOTL_UAV_MOTOR/PID Controller/Saturation Fdbk/Disabled'
 * '<S45>'  : 'VOTL_UAV_MOTOR/PID Controller/Sum/Sum_PID'
 * '<S46>'  : 'VOTL_UAV_MOTOR/PID Controller/Sum Fdbk/Disabled'
 * '<S47>'  : 'VOTL_UAV_MOTOR/PID Controller/Tracking Mode/Disabled'
 * '<S48>'  : 'VOTL_UAV_MOTOR/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S49>'  : 'VOTL_UAV_MOTOR/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S50>'  : 'VOTL_UAV_MOTOR/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S51>'  : 'VOTL_UAV_MOTOR/PID Controller/postSat Signal/Forward_Path'
 * '<S52>'  : 'VOTL_UAV_MOTOR/PID Controller/preInt Signal/Internal PreInt'
 * '<S53>'  : 'VOTL_UAV_MOTOR/PID Controller/preSat Signal/Forward_Path'
 */
#endif                                 /* PID0_h_ */
