//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: VisionHelicopter.cpp
//
// Code generated for Simulink model 'VisionHelicopter'.
//
// Model version                  : 1.10
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Sun Jul  5 14:59:06 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#include "VisionHelicopter.h"
#include <cmath>
#include "rtwtypes.h"

//
// This function updates continuous states using the ODE3 fixed-step
// solver algorithm
//
void VisionHelicopter::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  // Solver Matrices
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
  int_T nXc { 20 };

  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  // Save the state values at time t in y, we'll use x as ynew.
  (void) std::memcpy(y, x,
                     static_cast<uint_T>(nXc)*sizeof(real_T));

  // Assumes that rtsiSetT and ModelOutputs are up-to-date
  // f0 = f(t,y)
  rtsiSetdX(si, f0);
  VisionHelicopter_derivatives();

  // f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*));
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  this->step();
  VisionHelicopter_derivatives();

  // f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*));
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  this->step();
  VisionHelicopter_derivatives();

  // tnew = t + hA(3);
  // ynew = y + f*hB(:,3);
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

// Model step function
void VisionHelicopter::step()
{
  real_T deltaT_tmp;
  real_T riseValLimit;
  real_T rtb_Sum_o;
  real_T rtb_thrustfinal;
  boolean_T limitedCache;
  if ((&VisionHelicopter_M)->isMajorTimeStep()) {
    // set solver stop time
    rtsiSetSolverStopTime(&(&VisionHelicopter_M)->solverInfo,
                          (((&VisionHelicopter_M)->Timing.clockTick0+1)*
      (&VisionHelicopter_M)->Timing.stepSize0));
  }                                    // end MajorTimeStep

  // Update absolute time of base rate at minor time step
  if ((&VisionHelicopter_M)->isMinorTimeStep()) {
    (&VisionHelicopter_M)->Timing.t[0] = rtsiGetT(&(&VisionHelicopter_M)
      ->solverInfo);
  }

  // Gain: '<S5>/Gain' incorporates:
  //   StateSpace: '<Root>/Plant (Pitch)'
  //   Sum: '<S5>/Sum'
  //   TransferFcn: '<S5>/Low Pass Filter'

  VisionHelicopter_B.RateLimiter = (VisionHelicopter_P.LowPass_Filter_Coef *
    VisionHelicopter_X.LowPassFilter_CSTATE -
    VisionHelicopter_X.PlantPitch_CSTATE[0U]) * VisionHelicopter_P.PitchRoll_Kp + VisionHelicopter_P.PitchRoll_Kd *
    VisionHelicopter_X.PlantPitch_CSTATE[1U];

  // RateLimiter: '<S5>/Rate Limiter' incorporates:
  //   Gain: '<S5>/Gain'

  if (!(VisionHelicopter_DW.LastMajorTime == (rtInf))) {
    deltaT_tmp = (&VisionHelicopter_M)->Timing.t[0];
    rtb_thrustfinal = deltaT_tmp - VisionHelicopter_DW.LastMajorTime;
    if (VisionHelicopter_DW.LastMajorTime == deltaT_tmp) {
      if (VisionHelicopter_DW.PrevLimited) {
        // Gain: '<S5>/Gain' incorporates:
        //   RateLimiter: '<S5>/Rate Limiter'

        VisionHelicopter_B.RateLimiter = VisionHelicopter_DW.PrevY;
      }
    } else {
      riseValLimit = rtb_thrustfinal * VisionHelicopter_P.RateLimit_Rise;
      deltaT_tmp = VisionHelicopter_B.RateLimiter - VisionHelicopter_DW.PrevY;
      if (deltaT_tmp > riseValLimit) {
        // RateLimiter: '<S5>/Rate Limiter'
        VisionHelicopter_B.RateLimiter = VisionHelicopter_DW.PrevY +
          riseValLimit;
        limitedCache = true;
      } else {
        rtb_thrustfinal *= -VisionHelicopter_P.RateLimit_Rise;
        if (deltaT_tmp < rtb_thrustfinal) {
          // RateLimiter: '<S5>/Rate Limiter'
          VisionHelicopter_B.RateLimiter = VisionHelicopter_DW.PrevY +
            rtb_thrustfinal;
          limitedCache = true;
        } else {
          limitedCache = false;
        }
      }

      if (rtsiIsModeUpdateTimeStep(&(&VisionHelicopter_M)->solverInfo)) {
        VisionHelicopter_DW.PrevLimited = limitedCache;
      }
    }
  }

  // End of RateLimiter: '<S5>/Rate Limiter'

  // Saturate: '<S5>/Saturation'
  if (VisionHelicopter_B.RateLimiter > VisionHelicopter_P.Sat_Upper) {
    // Saturate: '<S5>/Saturation'
    VisionHelicopter_B.Saturation = VisionHelicopter_P.Sat_Upper;
  } else if (VisionHelicopter_B.RateLimiter < -VisionHelicopter_P.Sat_Upper) {
    // Saturate: '<S5>/Saturation'
    VisionHelicopter_B.Saturation = -VisionHelicopter_P.Sat_Upper;
  } else {
    // Saturate: '<S5>/Saturation'
    VisionHelicopter_B.Saturation = VisionHelicopter_B.RateLimiter;
  }

  // End of Saturate: '<S5>/Saturation'

  // Gain: '<S6>/Gain' incorporates:
  //   StateSpace: '<Root>/Plant (Roll)'
  //   Sum: '<S6>/Sum'
  //   TransferFcn: '<S6>/Low Pass Filter'

  VisionHelicopter_B.RateLimiter_e = (VisionHelicopter_P.LowPass_Filter_Coef *
    VisionHelicopter_X.LowPassFilter_CSTATE_b -
    VisionHelicopter_X.PlantRoll_CSTATE[0U]) * VisionHelicopter_P.PitchRoll_Kp + VisionHelicopter_P.PitchRoll_Kd *
    VisionHelicopter_X.PlantRoll_CSTATE[1U];

  // RateLimiter: '<S6>/Rate Limiter' incorporates:
  //   Gain: '<S6>/Gain'

  if (!(VisionHelicopter_DW.LastMajorTime_l == (rtInf))) {
    deltaT_tmp = (&VisionHelicopter_M)->Timing.t[0];
    rtb_thrustfinal = deltaT_tmp - VisionHelicopter_DW.LastMajorTime_l;
    if (VisionHelicopter_DW.LastMajorTime_l == deltaT_tmp) {
      if (VisionHelicopter_DW.PrevLimited_o) {
        // Gain: '<S6>/Gain' incorporates:
        //   RateLimiter: '<S6>/Rate Limiter'

        VisionHelicopter_B.RateLimiter_e = VisionHelicopter_DW.PrevY_p;
      }
    } else {
      riseValLimit = rtb_thrustfinal * VisionHelicopter_P.RateLimit_Rise;
      deltaT_tmp = VisionHelicopter_B.RateLimiter_e -
        VisionHelicopter_DW.PrevY_p;
      if (deltaT_tmp > riseValLimit) {
        // RateLimiter: '<S6>/Rate Limiter'
        VisionHelicopter_B.RateLimiter_e = VisionHelicopter_DW.PrevY_p +
          riseValLimit;
        limitedCache = true;
      } else {
        rtb_thrustfinal *= -VisionHelicopter_P.RateLimit_Rise;
        if (deltaT_tmp < rtb_thrustfinal) {
          // RateLimiter: '<S6>/Rate Limiter'
          VisionHelicopter_B.RateLimiter_e = VisionHelicopter_DW.PrevY_p +
            rtb_thrustfinal;
          limitedCache = true;
        } else {
          limitedCache = false;
        }
      }

      if (rtsiIsModeUpdateTimeStep(&(&VisionHelicopter_M)->solverInfo)) {
        VisionHelicopter_DW.PrevLimited_o = limitedCache;
      }
    }
  }

  // End of RateLimiter: '<S6>/Rate Limiter'

  // Saturate: '<S6>/Saturation'
  if (VisionHelicopter_B.RateLimiter_e > VisionHelicopter_P.Sat_Upper) {
    // Saturate: '<S6>/Saturation'
    VisionHelicopter_B.Saturation_a = VisionHelicopter_P.Sat_Upper;
  } else if (VisionHelicopter_B.RateLimiter_e < -VisionHelicopter_P.Sat_Upper) {
    // Saturate: '<S6>/Saturation'
    VisionHelicopter_B.Saturation_a = -VisionHelicopter_P.Sat_Upper;
  } else {
    // Saturate: '<S6>/Saturation'
    VisionHelicopter_B.Saturation_a = VisionHelicopter_B.RateLimiter_e;
  }

  // End of Saturate: '<S6>/Saturation'

  // Sum: '<S8>/Sum' incorporates:
  //   Integrator: '<Root>/Integrator1'
  //   TransferFcn: '<S8>/Low Pass Filter'

  VisionHelicopter_B.Sum = VisionHelicopter_P.LowPass_Filter_Coef *
    VisionHelicopter_X.LowPassFilter_CSTATE_j -
    VisionHelicopter_X.Integrator1_CSTATE;

  // Integrator: '<S150>/Integrator'
  // Limited  Integrator
  if (VisionHelicopter_X.Integrator_CSTATE >= VisionHelicopter_P.Integrator_Upper) {
    VisionHelicopter_X.Integrator_CSTATE = VisionHelicopter_P.Integrator_Upper;
  } else if (VisionHelicopter_X.Integrator_CSTATE <= -VisionHelicopter_P.Integrator_Upper) {
    VisionHelicopter_X.Integrator_CSTATE = -VisionHelicopter_P.Integrator_Upper;
  }

  // Gain: '<S153>/Filter Coefficient' incorporates:
  //   Gain: '<S143>/Derivative Gain'
  //   Integrator: '<S145>/Filter'
  //   Sum: '<S145>/SumD'

  VisionHelicopter_B.FilterCoefficient = (0.0 * VisionHelicopter_B.Sum -
    VisionHelicopter_X.Filter_CSTATE) * VisionHelicopter_P.Filter_Coef;

  // Sum: '<S4>/Sum' incorporates:
  //   SecondOrderIntegrator: '<Root>/z'
  //   TransferFcn: '<S4>/Low Pass Filter'

  rtb_Sum_o = VisionHelicopter_P.Alt_Filter_Coef * VisionHelicopter_X.LowPassFilter_CSTATE_c -
    VisionHelicopter_X.z_CSTATE[0];

  // Integrator: '<S44>/Integrator'
  // Limited  Integrator
  if (VisionHelicopter_X.Integrator_CSTATE_f >= VisionHelicopter_P.Integrator_Upper) {
    VisionHelicopter_X.Integrator_CSTATE_f = VisionHelicopter_P.Integrator_Upper;
  } else if (VisionHelicopter_X.Integrator_CSTATE_f <= -VisionHelicopter_P.Integrator_Upper) {
    VisionHelicopter_X.Integrator_CSTATE_f = -VisionHelicopter_P.Integrator_Upper;
  }

  // Gain: '<S47>/Filter Coefficient' incorporates:
  //   Gain: '<S37>/Derivative Gain'
  //   Integrator: '<S39>/Filter'
  //   Sum: '<S39>/SumD'

  VisionHelicopter_B.FilterCoefficient_a = (0.0 * rtb_Sum_o -
    VisionHelicopter_X.Filter_CSTATE_l) * VisionHelicopter_P.Filter_Coef;

  // Sum: '<S53>/Sum' incorporates:
  //   Gain: '<S49>/Proportional Gain'
  //   Integrator: '<S44>/Integrator'

  VisionHelicopter_B.Sum_g = (VisionHelicopter_P.RateLimit_Rise * rtb_Sum_o +
    VisionHelicopter_X.Integrator_CSTATE_f) +
    VisionHelicopter_B.FilterCoefficient_a;

  // Sum: '<S4>/thrust_total' incorporates:
  //   Constant: '<S4>/g'
  //   Gain: '<S4>/Fdrag'
  //   Gain: '<S4>/Fdrone'
  //   Sum: '<S4>/Sum1'
  //   TransferFcn: '<S4>/Transfer Fcn'

  VisionHelicopter_B.RateLimiter_ey = ((VisionHelicopter_P.Thrust_Transfer_Gain *
    VisionHelicopter_X.TransferFcn_CSTATE + VisionHelicopter_P.Filter_Coef * VisionHelicopter_B.Sum_g) +
    VisionHelicopter_P.Gravity) * VisionHelicopter_P.Sat_Upper + VisionHelicopter_P.Thrust_Base_Gain * VisionHelicopter_B.Sum_g;

  // RateLimiter: '<S4>/Rate Limiter'
  if (!(VisionHelicopter_DW.LastMajorTime_h == (rtInf))) {
    deltaT_tmp = (&VisionHelicopter_M)->Timing.t[0];
    rtb_thrustfinal = deltaT_tmp - VisionHelicopter_DW.LastMajorTime_h;
    if (VisionHelicopter_DW.LastMajorTime_h == deltaT_tmp) {
      if (VisionHelicopter_DW.PrevLimited_oz) {
        // Sum: '<S4>/thrust_total' incorporates:
        //   RateLimiter: '<S4>/Rate Limiter'

        VisionHelicopter_B.RateLimiter_ey = VisionHelicopter_DW.PrevY_h;
      }
    } else {
      riseValLimit = rtb_thrustfinal * VisionHelicopter_P.Thrust_Rate_Rise;
      deltaT_tmp = VisionHelicopter_B.RateLimiter_ey -
        VisionHelicopter_DW.PrevY_h;
      if (deltaT_tmp > riseValLimit) {
        // Sum: '<S4>/thrust_total' incorporates:
        //   RateLimiter: '<S4>/Rate Limiter'

        VisionHelicopter_B.RateLimiter_ey = VisionHelicopter_DW.PrevY_h +
          riseValLimit;
        limitedCache = true;
      } else {
        rtb_thrustfinal *= -VisionHelicopter_P.Thrust_Rate_Rise;
        if (deltaT_tmp < rtb_thrustfinal) {
          // Sum: '<S4>/thrust_total' incorporates:
          //   RateLimiter: '<S4>/Rate Limiter'

          VisionHelicopter_B.RateLimiter_ey = VisionHelicopter_DW.PrevY_h +
            rtb_thrustfinal;
          limitedCache = true;
        } else {
          limitedCache = false;
        }
      }

      if (rtsiIsModeUpdateTimeStep(&(&VisionHelicopter_M)->solverInfo)) {
        VisionHelicopter_DW.PrevLimited_oz = limitedCache;
      }
    }
  }

  // End of RateLimiter: '<S4>/Rate Limiter'

  // Saturate: '<S4>/thrust final'
  if (VisionHelicopter_B.RateLimiter_ey > VisionHelicopter_P.Thrust_Sat_Upper) {
    rtb_thrustfinal = VisionHelicopter_P.Thrust_Sat_Upper;
  } else if (VisionHelicopter_B.RateLimiter_ey < VisionHelicopter_P.Alt_Filter_Coef) {
    rtb_thrustfinal = VisionHelicopter_P.Alt_Filter_Coef;
  } else {
    rtb_thrustfinal = VisionHelicopter_B.RateLimiter_ey;
  }

  // End of Saturate: '<S4>/thrust final'

  // Product: '<S8>/Divide' incorporates:
  //   Gain: '<S8>/F_drag'
  //   Gain: '<S8>/F_req'
  //   Integrator: '<Root>/Integrator1'
  //   Integrator: '<S150>/Integrator'
  //   Sum: '<S159>/Sum'
  //   Sum: '<S8>/Sum1'

  deltaT_tmp = (((VisionHelicopter_B.Sum + VisionHelicopter_X.Integrator_CSTATE)
                 + VisionHelicopter_B.FilterCoefficient) * VisionHelicopter_P.Sat_Upper + VisionHelicopter_P.Drag_Coef *
                VisionHelicopter_X.Integrator1_CSTATE) / rtb_thrustfinal;

  // Saturate: '<S8>/Saturation'
  if (deltaT_tmp > VisionHelicopter_P.Pitch_Sat_Upper) {
    // Gain: '<S8>/final_pitch'
    VisionHelicopter_B.final_pitch = -VisionHelicopter_P.Pitch_Sat_Upper;
  } else if (deltaT_tmp < -VisionHelicopter_P.Pitch_Sat_Upper) {
    // Gain: '<S8>/final_pitch'
    VisionHelicopter_B.final_pitch = VisionHelicopter_P.Pitch_Sat_Upper;
  } else {
    // Gain: '<S8>/final_pitch'
    VisionHelicopter_B.final_pitch = -deltaT_tmp;
  }

  // End of Saturate: '<S8>/Saturation'

  // MATLAB Function: '<Root>/MATLAB Function2' incorporates:
  //   Integrator: '<Root>/Integrator1'

  VisionHelicopter_B.vy_dot = (-rtb_thrustfinal * std::sin
    (VisionHelicopter_B.final_pitch) - VisionHelicopter_P.Drag_Coef *
    VisionHelicopter_X.Integrator1_CSTATE) / VisionHelicopter_P.Sat_Upper;

  // MATLAB Function: '<Root>/MATLAB Function' incorporates:
  //   SecondOrderIntegrator: '<Root>/z'

  VisionHelicopter_B.z_ddot = ((rtb_thrustfinal - VisionHelicopter_P.Hover_Thrust) - VisionHelicopter_P.Drag_Coef *
    VisionHelicopter_X.z_CSTATE[1]) / VisionHelicopter_P.Sat_Upper;

  // Sum: '<S7>/Sum' incorporates:
  //   Integrator: '<Root>/vx_curr'
  //   TransferFcn: '<S7>/Low Pass Filter'

  VisionHelicopter_B.Sum_d = VisionHelicopter_P.LowPass_Filter_Coef *
    VisionHelicopter_X.LowPassFilter_CSTATE_d -
    VisionHelicopter_X.vx_curr_CSTATE;

  // Integrator: '<S97>/Integrator'
  // Limited  Integrator
  if (VisionHelicopter_X.Integrator_CSTATE_k >= VisionHelicopter_P.Integrator_Upper) {
    VisionHelicopter_X.Integrator_CSTATE_k = VisionHelicopter_P.Integrator_Upper;
  } else if (VisionHelicopter_X.Integrator_CSTATE_k <= -VisionHelicopter_P.Integrator_Upper) {
    VisionHelicopter_X.Integrator_CSTATE_k = -VisionHelicopter_P.Integrator_Upper;
  }

  // Gain: '<S100>/Filter Coefficient' incorporates:
  //   Gain: '<S90>/Derivative Gain'
  //   Integrator: '<S92>/Filter'
  //   Sum: '<S92>/SumD'

  VisionHelicopter_B.FilterCoefficient_h = (0.0 * VisionHelicopter_B.Sum_d -
    VisionHelicopter_X.Filter_CSTATE_n) * VisionHelicopter_P.Filter_Coef;

  // Product: '<S7>/Divide' incorporates:
  //   Gain: '<S7>/F_drag'
  //   Gain: '<S7>/F_req'
  //   Integrator: '<Root>/vx_curr'
  //   Integrator: '<S97>/Integrator'
  //   Sum: '<S106>/Sum'
  //   Sum: '<S7>/Sum1'

  deltaT_tmp = (((VisionHelicopter_B.Sum_d +
                  VisionHelicopter_X.Integrator_CSTATE_k) +
                 VisionHelicopter_B.FilterCoefficient_h) * VisionHelicopter_P.Sat_Upper + VisionHelicopter_P.Drag_Coef *
                VisionHelicopter_X.vx_curr_CSTATE) / rtb_thrustfinal;

  // Saturate: '<S7>/Saturation'
  if (deltaT_tmp > VisionHelicopter_P.Pitch_Sat_Upper) {
    // Gain: '<S7>/final_pitch'
    VisionHelicopter_B.final_pitch_b = -VisionHelicopter_P.Pitch_Sat_Upper;
  } else if (deltaT_tmp < -VisionHelicopter_P.Pitch_Sat_Upper) {
    // Gain: '<S7>/final_pitch'
    VisionHelicopter_B.final_pitch_b = VisionHelicopter_P.Pitch_Sat_Upper;
  } else {
    // Gain: '<S7>/final_pitch'
    VisionHelicopter_B.final_pitch_b = -deltaT_tmp;
  }

  // End of Saturate: '<S7>/Saturation'

  // MATLAB Function: '<Root>/MATLAB Function1' incorporates:
  //   Integrator: '<Root>/vx_curr'

  VisionHelicopter_B.vx_dot = (-rtb_thrustfinal * std::sin
    (VisionHelicopter_B.final_pitch_b) - VisionHelicopter_P.Drag_Coef * VisionHelicopter_X.vx_curr_CSTATE)
    / VisionHelicopter_P.Sat_Upper;

  // Gain: '<S41>/Integral Gain'
  VisionHelicopter_B.IntegralGain = VisionHelicopter_P.Alt_Filter_Coef * rtb_Sum_o;
  if ((&VisionHelicopter_M)->isMajorTimeStep()) {
    // Update for RateLimiter: '<S5>/Rate Limiter' incorporates:
    //   RateLimiter: '<S4>/Rate Limiter'
    //   RateLimiter: '<S6>/Rate Limiter'

    VisionHelicopter_DW.PrevY = VisionHelicopter_B.RateLimiter;
    VisionHelicopter_DW.LastMajorTime = (&VisionHelicopter_M)->Timing.t[0];

    // Update for RateLimiter: '<S6>/Rate Limiter'
    VisionHelicopter_DW.PrevY_p = VisionHelicopter_B.RateLimiter_e;
    VisionHelicopter_DW.LastMajorTime_l = VisionHelicopter_DW.LastMajorTime;

    // Update for RateLimiter: '<S4>/Rate Limiter'
    VisionHelicopter_DW.PrevY_h = VisionHelicopter_B.RateLimiter_ey;
    VisionHelicopter_DW.LastMajorTime_h = VisionHelicopter_DW.LastMajorTime;
  }                                    // end MajorTimeStep

  if ((&VisionHelicopter_M)->isMajorTimeStep()) {
    rt_ertODEUpdateContinuousStates(&(&VisionHelicopter_M)->solverInfo);

    // Update absolute time for base rate
    // The "clockTick0" counts the number of times the code of this task has
    //  been executed. The absolute time is the multiplication of "clockTick0"
    //  and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
    //  overflow during the application lifespan selected.

    ++(&VisionHelicopter_M)->Timing.clockTick0;
    (&VisionHelicopter_M)->Timing.t[0] = rtsiGetSolverStopTime
      (&(&VisionHelicopter_M)->solverInfo);

    {
      // Update absolute timer for sample time: [1.3s, 0.0s]
      // The "clockTick1" counts the number of times the code of this task has
      //  been executed. The resolution of this integer timer is 1.3, which is the step size
      //  of the task. Size of "clockTick1" ensures timer will not overflow during the
      //  application lifespan selected.

      (&VisionHelicopter_M)->Timing.clockTick1++;
    }
  }                                    // end MajorTimeStep
}

// Derivatives for root system: '<Root>'
void VisionHelicopter::VisionHelicopter_derivatives()
{
  VisionHelicopter::XDot_VisionHelicopter_T *_rtXdot;
  uint32_T ri;
  boolean_T lsat;
  boolean_T usat;
  _rtXdot = ((XDot_VisionHelicopter_T *) (&VisionHelicopter_M)->derivs);

  // Derivatives for StateSpace: '<Root>/Plant (Pitch)'
  _rtXdot->PlantPitch_CSTATE[0] = 0.0;
  _rtXdot->PlantPitch_CSTATE[1] = 0.0;
  for (ri = 0U; ri < 2U; ri++) {
    _rtXdot->PlantPitch_CSTATE[ri] += VisionHelicopter_ConstP.pooled1[ri] *
      VisionHelicopter_X.PlantPitch_CSTATE[1U];
  }

  _rtXdot->PlantPitch_CSTATE[1U] += VisionHelicopter_P.Plant_Actuator_Gain * VisionHelicopter_B.Saturation;

  // End of Derivatives for StateSpace: '<Root>/Plant (Pitch)'

  // Derivatives for TransferFcn: '<S5>/Low Pass Filter'
  _rtXdot->LowPassFilter_CSTATE = -VisionHelicopter_P.LowPass_Filter_Coef *
    VisionHelicopter_X.LowPassFilter_CSTATE;
  _rtXdot->LowPassFilter_CSTATE += VisionHelicopter_B.final_pitch_b;

  // Derivatives for StateSpace: '<Root>/Plant (Roll)'
  _rtXdot->PlantRoll_CSTATE[0] = 0.0;
  _rtXdot->PlantRoll_CSTATE[1] = 0.0;
  for (ri = 0U; ri < 2U; ri++) {
    _rtXdot->PlantRoll_CSTATE[ri] += VisionHelicopter_ConstP.pooled1[ri] *
      VisionHelicopter_X.PlantRoll_CSTATE[1U];
  }

  _rtXdot->PlantRoll_CSTATE[1U] += VisionHelicopter_P.Plant_Actuator_Gain * VisionHelicopter_B.Saturation_a;

  // End of Derivatives for StateSpace: '<Root>/Plant (Roll)'

  // Derivatives for TransferFcn: '<S6>/Low Pass Filter'
  _rtXdot->LowPassFilter_CSTATE_b = -VisionHelicopter_P.LowPass_Filter_Coef *
    VisionHelicopter_X.LowPassFilter_CSTATE_b;
  _rtXdot->LowPassFilter_CSTATE_b += VisionHelicopter_B.final_pitch;

  // Derivatives for Integrator: '<Root>/Integrator1'
  _rtXdot->Integrator1_CSTATE = VisionHelicopter_B.vy_dot;

  // Derivatives for TransferFcn: '<S8>/Low Pass Filter'
  _rtXdot->LowPassFilter_CSTATE_j = -VisionHelicopter_P.LowPass_Filter_Coef *
    VisionHelicopter_X.LowPassFilter_CSTATE_j;

  // Derivatives for Integrator: '<S150>/Integrator'
  lsat = (VisionHelicopter_X.Integrator_CSTATE <= -VisionHelicopter_P.Integrator_Upper);
  usat = (VisionHelicopter_X.Integrator_CSTATE >= VisionHelicopter_P.Integrator_Upper);
  if (((!lsat) && (!usat)) || (lsat && (VisionHelicopter_B.Sum > 0.0)) || (usat &&
       (VisionHelicopter_B.Sum < 0.0))) {
    _rtXdot->Integrator_CSTATE = VisionHelicopter_B.Sum;
  } else {
    // in saturation
    _rtXdot->Integrator_CSTATE = 0.0;
  }

  // End of Derivatives for Integrator: '<S150>/Integrator'

  // Derivatives for Integrator: '<S145>/Filter'
  _rtXdot->Filter_CSTATE = VisionHelicopter_B.FilterCoefficient;

  // Derivatives for TransferFcn: '<S4>/Low Pass Filter'
  _rtXdot->LowPassFilter_CSTATE_c = -VisionHelicopter_P.Alt_Filter_Coef *
    VisionHelicopter_X.LowPassFilter_CSTATE_c;
  _rtXdot->LowPassFilter_CSTATE_c += VisionHelicopter_P.Alt_LowPass_Input;

  // Derivatives for SecondOrderIntegrator: '<Root>/z'
  if (VisionHelicopter_DW.z_MODE == 0) {
    _rtXdot->z_CSTATE[0] = VisionHelicopter_X.z_CSTATE[1];
    _rtXdot->z_CSTATE[1] = VisionHelicopter_B.z_ddot;
  }

  // End of Derivatives for SecondOrderIntegrator: '<Root>/z'

  // Derivatives for Integrator: '<S44>/Integrator'
  lsat = (VisionHelicopter_X.Integrator_CSTATE_f <= -VisionHelicopter_P.Integrator_Upper);
  usat = (VisionHelicopter_X.Integrator_CSTATE_f >= VisionHelicopter_P.Integrator_Upper);
  if (((!lsat) && (!usat)) || (lsat && (VisionHelicopter_B.IntegralGain > 0.0)) ||
      (usat && (VisionHelicopter_B.IntegralGain < 0.0))) {
    _rtXdot->Integrator_CSTATE_f = VisionHelicopter_B.IntegralGain;
  } else {
    // in saturation
    _rtXdot->Integrator_CSTATE_f = 0.0;
  }

  // End of Derivatives for Integrator: '<S44>/Integrator'

  // Derivatives for Integrator: '<S39>/Filter'
  _rtXdot->Filter_CSTATE_l = VisionHelicopter_B.FilterCoefficient_a;

  // Derivatives for TransferFcn: '<S4>/Transfer Fcn'
  _rtXdot->TransferFcn_CSTATE = -VisionHelicopter_P.Filter_Coef * VisionHelicopter_X.TransferFcn_CSTATE;
  _rtXdot->TransferFcn_CSTATE += VisionHelicopter_B.Sum_g;

  // Derivatives for Integrator: '<Root>/vx_curr'
  _rtXdot->vx_curr_CSTATE = VisionHelicopter_B.vx_dot;

  // Derivatives for TransferFcn: '<S7>/Low Pass Filter' incorporates:
  //   Constant: '<Root>/Constant1'

  _rtXdot->LowPassFilter_CSTATE_d = -VisionHelicopter_P.LowPass_Filter_Coef *
    VisionHelicopter_X.LowPassFilter_CSTATE_d;
  _rtXdot->LowPassFilter_CSTATE_d += VisionHelicopter_P.Vx_LowPass_Input;

  // Derivatives for Integrator: '<S97>/Integrator'
  lsat = (VisionHelicopter_X.Integrator_CSTATE_k <= -VisionHelicopter_P.Integrator_Upper);
  usat = (VisionHelicopter_X.Integrator_CSTATE_k >= VisionHelicopter_P.Integrator_Upper);
  if (((!lsat) && (!usat)) || (lsat && (VisionHelicopter_B.Sum_d > 0.0)) ||
      (usat && (VisionHelicopter_B.Sum_d < 0.0))) {
    _rtXdot->Integrator_CSTATE_k = VisionHelicopter_B.Sum_d;
  } else {
    // in saturation
    _rtXdot->Integrator_CSTATE_k = 0.0;
  }

  // End of Derivatives for Integrator: '<S97>/Integrator'

  // Derivatives for Integrator: '<S92>/Filter'
  _rtXdot->Filter_CSTATE_n = VisionHelicopter_B.FilterCoefficient_h;
}

// Model initialize function
void VisionHelicopter::initialize()
{
  // Registration code
  {
    // Setup solver object
    rtsiSetSimTimeStepPtr(&(&VisionHelicopter_M)->solverInfo,
                          &(&VisionHelicopter_M)->Timing.simTimeStep);
    rtsiSetTPtr(&(&VisionHelicopter_M)->solverInfo, (&VisionHelicopter_M)
                ->getTPtrPtr());
    rtsiSetStepSizePtr(&(&VisionHelicopter_M)->solverInfo, &(&VisionHelicopter_M)
                       ->Timing.stepSize0);
    rtsiSetdXPtr(&(&VisionHelicopter_M)->solverInfo, &(&VisionHelicopter_M)
                 ->derivs);
    rtsiSetContStatesPtr(&(&VisionHelicopter_M)->solverInfo, (real_T **)
                         &(&VisionHelicopter_M)->contStates);
    rtsiSetNumContStatesPtr(&(&VisionHelicopter_M)->solverInfo,
      &(&VisionHelicopter_M)->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&VisionHelicopter_M)->solverInfo,
      &(&VisionHelicopter_M)->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&VisionHelicopter_M)->solverInfo,
      &(&VisionHelicopter_M)->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&VisionHelicopter_M)->solverInfo,
      &(&VisionHelicopter_M)->periodicContStateRanges);
    rtsiSetContStateDisabledPtr(&(&VisionHelicopter_M)->solverInfo, (boolean_T**)
      &(&VisionHelicopter_M)->contStateDisabled);
    rtsiSetErrorStatusPtr(&(&VisionHelicopter_M)->solverInfo,
                          (&VisionHelicopter_M)->getErrorStatusPtr());
    rtsiSetRTModelPtr(&(&VisionHelicopter_M)->solverInfo, (&VisionHelicopter_M));
  }

  rtsiSetSimTimeStep(&(&VisionHelicopter_M)->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&(&VisionHelicopter_M)->solverInfo, false);
  rtsiSetIsContModeFrozen(&(&VisionHelicopter_M)->solverInfo, false);
  (&VisionHelicopter_M)->intgData.y = (&VisionHelicopter_M)->odeY;
  (&VisionHelicopter_M)->intgData.f[0] = (&VisionHelicopter_M)->odeF[0];
  (&VisionHelicopter_M)->intgData.f[1] = (&VisionHelicopter_M)->odeF[1];
  (&VisionHelicopter_M)->intgData.f[2] = (&VisionHelicopter_M)->odeF[2];
  (&VisionHelicopter_M)->contStates = ((X_VisionHelicopter_T *)
    &VisionHelicopter_X);
  (&VisionHelicopter_M)->contStateDisabled = ((XDis_VisionHelicopter_T *)
    &VisionHelicopter_XDis);
  (&VisionHelicopter_M)->Timing.tStart = (0.0);
  rtsiSetSolverData(&(&VisionHelicopter_M)->solverInfo, static_cast<void *>
                    (&(&VisionHelicopter_M)->intgData));
  rtsiSetSolverName(&(&VisionHelicopter_M)->solverInfo,"ode3");
  (&VisionHelicopter_M)->setTPtr(&(&VisionHelicopter_M)->Timing.tArray[0]);
  (&VisionHelicopter_M)->Timing.stepSize0 = 0.01;

  // InitializeConditions for TransferFcn: '<S5>/Low Pass Filter'
  VisionHelicopter_X.LowPassFilter_CSTATE = 0.0;

  // InitializeConditions for RateLimiter: '<S5>/Rate Limiter'
  VisionHelicopter_DW.LastMajorTime = (rtInf);

  // InitializeConditions for StateSpace: '<Root>/Plant (Pitch)'
  VisionHelicopter_X.PlantPitch_CSTATE[0] = 0.0;

  // InitializeConditions for StateSpace: '<Root>/Plant (Roll)'
  VisionHelicopter_X.PlantRoll_CSTATE[0] = 0.0;

  // InitializeConditions for StateSpace: '<Root>/Plant (Pitch)'
  VisionHelicopter_X.PlantPitch_CSTATE[1] = 0.0;

  // InitializeConditions for StateSpace: '<Root>/Plant (Roll)'
  VisionHelicopter_X.PlantRoll_CSTATE[1] = 0.0;

  // InitializeConditions for TransferFcn: '<S6>/Low Pass Filter'
  VisionHelicopter_X.LowPassFilter_CSTATE_b = 0.0;

  // InitializeConditions for RateLimiter: '<S6>/Rate Limiter'
  VisionHelicopter_DW.LastMajorTime_l = (rtInf);

  // InitializeConditions for Integrator: '<Root>/Integrator1'
  VisionHelicopter_X.Integrator1_CSTATE = 0.0;

  // InitializeConditions for TransferFcn: '<S8>/Low Pass Filter'
  VisionHelicopter_X.LowPassFilter_CSTATE_j = 0.0;

  // InitializeConditions for Integrator: '<S150>/Integrator'
  VisionHelicopter_X.Integrator_CSTATE = 0.0;

  // InitializeConditions for Integrator: '<S145>/Filter'
  VisionHelicopter_X.Filter_CSTATE = 0.0;

  // InitializeConditions for TransferFcn: '<S4>/Low Pass Filter'
  VisionHelicopter_X.LowPassFilter_CSTATE_c = 0.0;

  // InitializeConditions for SecondOrderIntegrator: '<Root>/z'
  VisionHelicopter_X.z_CSTATE[0] = 0.0;
  VisionHelicopter_X.z_CSTATE[1] = 0.0;

  // InitializeConditions for Integrator: '<S44>/Integrator'
  VisionHelicopter_X.Integrator_CSTATE_f = 0.0;

  // InitializeConditions for Integrator: '<S39>/Filter'
  VisionHelicopter_X.Filter_CSTATE_l = 0.0;

  // InitializeConditions for TransferFcn: '<S4>/Transfer Fcn'
  VisionHelicopter_X.TransferFcn_CSTATE = 0.0;

  // InitializeConditions for RateLimiter: '<S4>/Rate Limiter'
  VisionHelicopter_DW.LastMajorTime_h = (rtInf);

  // InitializeConditions for Integrator: '<Root>/vx_curr'
  VisionHelicopter_X.vx_curr_CSTATE = 0.0;

  // InitializeConditions for TransferFcn: '<S7>/Low Pass Filter'
  VisionHelicopter_X.LowPassFilter_CSTATE_d = 0.0;

  // InitializeConditions for Integrator: '<S97>/Integrator'
  VisionHelicopter_X.Integrator_CSTATE_k = 0.0;

  // InitializeConditions for Integrator: '<S92>/Filter'
  VisionHelicopter_X.Filter_CSTATE_n = 0.0;
}

// Model terminate function
void VisionHelicopter::terminate()
{
  // (no terminate code required)
}

time_T** VisionHelicopter::RT_MODEL_VisionHelicopter_T::getTPtrPtr()
{
  return &(Timing.t);
}

boolean_T VisionHelicopter::RT_MODEL_VisionHelicopter_T::getStopRequested()
  const
{
  return (Timing.stopRequestedFlag);
}

void VisionHelicopter::RT_MODEL_VisionHelicopter_T::setStopRequested(boolean_T
  aStopRequested)
{
  (Timing.stopRequestedFlag = aStopRequested);
}

const char_T* VisionHelicopter::RT_MODEL_VisionHelicopter_T::getErrorStatus()
  const
{
  return (errorStatus);
}

void VisionHelicopter::RT_MODEL_VisionHelicopter_T::setErrorStatus(const char_T*
  const aErrorStatus)
{
  (errorStatus = aErrorStatus);
}

time_T* VisionHelicopter::RT_MODEL_VisionHelicopter_T::getTPtr() const
{
  return (Timing.t);
}

void VisionHelicopter::RT_MODEL_VisionHelicopter_T::setTPtr(time_T* aTPtr)
{
  (Timing.t = aTPtr);
}

boolean_T* VisionHelicopter::RT_MODEL_VisionHelicopter_T::getStopRequestedPtr()
{
  return (&(Timing.stopRequestedFlag));
}

const char_T** VisionHelicopter::RT_MODEL_VisionHelicopter_T::getErrorStatusPtr()
{
  return &errorStatus;
}

boolean_T VisionHelicopter::RT_MODEL_VisionHelicopter_T::isMajorTimeStep() const
{
  return ((Timing.simTimeStep) == MAJOR_TIME_STEP);
}

boolean_T VisionHelicopter::RT_MODEL_VisionHelicopter_T::isMinorTimeStep() const
{
  return ((Timing.simTimeStep) == MINOR_TIME_STEP);
}

time_T VisionHelicopter::RT_MODEL_VisionHelicopter_T::getTStart() const
{
  return (Timing.tStart);
}

// Constructor
VisionHelicopter::VisionHelicopter() :
  VisionHelicopter_B(),
  VisionHelicopter_DW(),
  VisionHelicopter_X(),
  VisionHelicopter_XDis(),
  VisionHelicopter_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
// Currently there is no destructor body generated.
VisionHelicopter::~VisionHelicopter() = default;

// Real-Time Model get method
VisionHelicopter::RT_MODEL_VisionHelicopter_T * VisionHelicopter::getRTM()
{
  return (&VisionHelicopter_M);
}

//
// File trailer for generated code.
//
// [EOF]
//
