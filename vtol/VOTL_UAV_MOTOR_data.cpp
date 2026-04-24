/*
 * VOTL_UAV_MOTOR_data.cpp
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

/* Block parameters (default storage) */
P_VOTL_UAV_MOTOR_T VOTL_UAV_MOTOR::VOTL_UAV_MOTOR_P{
  /* Mask Parameter: PIDController_D
   * Referenced by: '<S31>/Derivative Gain'
   */
  0.0,

  /* Mask Parameter: PIDController_I
   * Referenced by: '<S35>/Integral Gain'
   */
  1.0,

  /* Mask Parameter: PIDController_InitialConditionF
   * Referenced by: '<S33>/Filter'
   */
  0.0,

  /* Mask Parameter: PIDController_InitialConditio_c
   * Referenced by: '<S38>/Integrator'
   */
  0.0,

  /* Mask Parameter: PIDController_N
   * Referenced by: '<S41>/Filter Coefficient'
   */
  100.0,

  /* Mask Parameter: PIDController_P
   * Referenced by: '<S43>/Proportional Gain'
   */
  1.0,

  /* Mask Parameter: RepeatingSequence_rep_seq_y
   * Referenced by: '<S1>/Look-Up Table1'
   */
  { 0.0, 1000.0 },

  /* Computed Parameter: Filter_gainval
   * Referenced by: '<S33>/Filter'
   */
  0.001,

  /* Computed Parameter: Integrator_gainval
   * Referenced by: '<S38>/Integrator'
   */
  0.001,

  /* Computed Parameter: TransferFcn_A
   * Referenced by: '<Root>/Transfer Fcn'
   */
  -100.0,

  /* Computed Parameter: TransferFcn_C
   * Referenced by: '<Root>/Transfer Fcn'
   */
  100.0,

  /* Expression: 0
   * Referenced by: '<Root>/Step'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<Root>/Step'
   */
  0.0,

  /* Expression: 500
   * Referenced by: '<Root>/Step'
   */
  500.0,

  /* Expression: 1000
   * Referenced by: '<Root>/Saturation'
   */
  1000.0,

  /* Expression: 0
   * Referenced by: '<Root>/Saturation'
   */
  0.0,

  /* Expression: period
   * Referenced by: '<S1>/Constant'
   */
  0.001,

  /* Expression: rep_seq_t - min(rep_seq_t)
   * Referenced by: '<S1>/Look-Up Table1'
   */
  { 0.0, 0.001 }
};
