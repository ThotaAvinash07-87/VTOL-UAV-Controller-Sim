/*
 * rtGetNaN.cpp
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

#include "rtwtypes.h"

extern "C"
{

#include "rtGetNaN.h"

}

extern "C"
{
  /* Return rtNaN needed by the generated code. */
  real_T rtGetNaN(void)
  {
    return rtNaN;
  }

  /* Return rtNaNF needed by the generated code. */
  real32_T rtGetNaNF(void)
  {
    return rtNaNF;
  }
}
