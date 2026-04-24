/*
 * PID0_data.c
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

/* Block parameters (default storage) */
P_PID0_T PID0_P = {
  /* Mask Parameter: PIDController_D
   * Referenced by: '<S29>/Derivative Gain'
   */
  0.0,

  /* Mask Parameter: PIDController_I
   * Referenced by: '<S33>/Integral Gain'
   */
  1.0,

  /* Mask Parameter: PIDController_InitialConditionF
   * Referenced by: '<S31>/Filter'
   */
  0.0,

  /* Mask Parameter: PIDController_InitialConditio_c
   * Referenced by: '<S36>/Integrator'
   */
  0.0,

  /* Mask Parameter: PIDController_N
   * Referenced by: '<S39>/Filter Coefficient'
   */
  100.0,

  /* Mask Parameter: PIDController_P
   * Referenced by: '<S41>/Proportional Gain'
   */
  1.0,

  /* Computed Parameter: Integrator_gainval
   * Referenced by: '<S36>/Integrator'
   */
  0.001,

  /* Computed Parameter: Filter_gainval
   * Referenced by: '<S31>/Filter'
   */
  0.001
};
