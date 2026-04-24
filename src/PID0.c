/*
 * PID0.c
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

#include "PID0.h"
#include "rtwtypes.h"
#include "PID0_private.h"
#include <string.h>

/* Block states (default storage) */
DW_PID0_T PID0_DW;

/* External inputs (root inport signals with default storage) */
ExtU_PID0_T PID0_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_PID0_T PID0_Y;

/* Real-time model */
static RT_MODEL_PID0_T PID0_M_;
RT_MODEL_PID0_T *const PID0_M = &PID0_M_;

/* Model step function */
void PID0_step(void)
{
  real_T rtb_FilterCoefficient;

  /* Gain: '<S39>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S31>/Filter'
   *  Gain: '<S29>/Derivative Gain'
   *  Inport: '<Root>/u'
   *  Sum: '<S31>/SumD'
   */
  rtb_FilterCoefficient = (PID0_P.PIDController_D * PID0_U.u -
    PID0_DW.Filter_DSTATE) * PID0_P.PIDController_N;

  /* Outport: '<Root>/y' incorporates:
   *  DiscreteIntegrator: '<S36>/Integrator'
   *  Gain: '<S41>/Proportional Gain'
   *  Inport: '<Root>/u'
   *  Sum: '<S45>/Sum'
   */
  PID0_Y.y = (PID0_P.PIDController_P * PID0_U.u + PID0_DW.Integrator_DSTATE) +
    rtb_FilterCoefficient;

  /* Update for DiscreteIntegrator: '<S36>/Integrator' incorporates:
   *  Gain: '<S33>/Integral Gain'
   *  Inport: '<Root>/u'
   */
  PID0_DW.Integrator_DSTATE += PID0_P.PIDController_I * PID0_U.u *
    PID0_P.Integrator_gainval;

  /* Update for DiscreteIntegrator: '<S31>/Filter' */
  PID0_DW.Filter_DSTATE += PID0_P.Filter_gainval * rtb_FilterCoefficient;

  /* Matfile logging */
  rt_UpdateTXYLogVars(PID0_M->rtwLogInfo, (&PID0_M->Timing.taskTime0));

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.001s, 0.0s] */
    if ((rtmGetTFinal(PID0_M)!=-1) &&
        !((rtmGetTFinal(PID0_M)-PID0_M->Timing.taskTime0) >
          PID0_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(PID0_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++PID0_M->Timing.clockTick0)) {
    ++PID0_M->Timing.clockTickH0;
  }

  PID0_M->Timing.taskTime0 = PID0_M->Timing.clockTick0 *
    PID0_M->Timing.stepSize0 + PID0_M->Timing.clockTickH0 *
    PID0_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void PID0_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)PID0_M, 0,
                sizeof(RT_MODEL_PID0_T));
  rtmSetTFinal(PID0_M, 0.05);
  PID0_M->Timing.stepSize0 = 0.001;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = (NULL);
    PID0_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(PID0_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(PID0_M->rtwLogInfo, (NULL));
    rtliSetLogT(PID0_M->rtwLogInfo, "tout");
    rtliSetLogX(PID0_M->rtwLogInfo, "");
    rtliSetLogXFinal(PID0_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(PID0_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(PID0_M->rtwLogInfo, 4);
    rtliSetLogMaxRows(PID0_M->rtwLogInfo, 0);
    rtliSetLogDecimation(PID0_M->rtwLogInfo, 1);
    rtliSetLogY(PID0_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(PID0_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(PID0_M->rtwLogInfo, (NULL));
  }

  /* states (dwork) */
  (void) memset((void *)&PID0_DW, 0,
                sizeof(DW_PID0_T));

  /* external inputs */
  PID0_U.u = 0.0;

  /* external outputs */
  PID0_Y.y = 0.0;

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(PID0_M->rtwLogInfo, 0.0, rtmGetTFinal(PID0_M),
    PID0_M->Timing.stepSize0, (&rtmGetErrorStatus(PID0_M)));

  /* InitializeConditions for DiscreteIntegrator: '<S36>/Integrator' */
  PID0_DW.Integrator_DSTATE = PID0_P.PIDController_InitialConditio_c;

  /* InitializeConditions for DiscreteIntegrator: '<S31>/Filter' */
  PID0_DW.Filter_DSTATE = PID0_P.PIDController_InitialConditionF;
}

/* Model terminate function */
void PID0_terminate(void)
{
  /* (no terminate code required) */
}
