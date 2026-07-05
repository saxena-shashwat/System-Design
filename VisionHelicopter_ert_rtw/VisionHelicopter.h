//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: VisionHelicopter.h
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
#ifndef VisionHelicopter_h_
#define VisionHelicopter_h_
#include <cmath>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_nonfinite.h"
#include "VisionHelicopter_types.h"

extern "C"
{

#include "rtGetInf.h"

}

#include <cstring>
#ifndef ODE3_INTG
#define ODE3_INTG

// ODE3 Integration Data
struct ODE3_IntgData {
  real_T *y;                           // output
  real_T *f[3];                        // derivatives
};

#endif

// Class declaration for model VisionHelicopter
class VisionHelicopter final
{
  // public data and function members
 public:
  // Block signals (default storage)
  struct B_VisionHelicopter_T {
    real_T RateLimiter;                // '<S5>/Rate Limiter'
    real_T Saturation;                 // '<S5>/Saturation'
    real_T RateLimiter_e;              // '<S6>/Rate Limiter'
    real_T Saturation_a;               // '<S6>/Saturation'
    real_T Sum;                        // '<S8>/Sum'
    real_T FilterCoefficient;          // '<S153>/Filter Coefficient'
    real_T FilterCoefficient_a;        // '<S47>/Filter Coefficient'
    real_T Sum_g;                      // '<S53>/Sum'
    real_T RateLimiter_ey;             // '<S4>/Rate Limiter'
    real_T final_pitch;                // '<S8>/final_pitch'
    real_T Sum_d;                      // '<S7>/Sum'
    real_T FilterCoefficient_h;        // '<S100>/Filter Coefficient'
    real_T final_pitch_b;              // '<S7>/final_pitch'
    real_T IntegralGain;               // '<S41>/Integral Gain'
    real_T vy_dot;                     // '<Root>/MATLAB Function2'
    real_T vx_dot;                     // '<Root>/MATLAB Function1'
    real_T z_ddot;                     // '<Root>/MATLAB Function'
  };

  // Block states (default storage) for system '<Root>'
  struct DW_VisionHelicopter_T {
    real_T PrevY;                      // '<S5>/Rate Limiter'
    real_T LastMajorTime;              // '<S5>/Rate Limiter'
    real_T PrevY_p;                    // '<S6>/Rate Limiter'
    real_T LastMajorTime_l;            // '<S6>/Rate Limiter'
    real_T PrevY_h;                    // '<S4>/Rate Limiter'
    real_T LastMajorTime_h;            // '<S4>/Rate Limiter'
    int_T z_MODE;                      // '<Root>/z'
    boolean_T PrevLimited;             // '<S5>/Rate Limiter'
    boolean_T PrevLimited_o;           // '<S6>/Rate Limiter'
    boolean_T z_DWORK1;                // '<Root>/z'
    boolean_T PrevLimited_oz;          // '<S4>/Rate Limiter'
  };

  // Continuous states (default storage)
  struct X_VisionHelicopter_T {
    real_T PlantPitch_CSTATE[2];       // '<Root>/Plant (Pitch)'
    real_T LowPassFilter_CSTATE;       // '<S5>/Low Pass Filter'
    real_T PlantRoll_CSTATE[2];        // '<Root>/Plant (Roll)'
    real_T LowPassFilter_CSTATE_b;     // '<S6>/Low Pass Filter'
    real_T Integrator1_CSTATE;         // '<Root>/Integrator1'
    real_T LowPassFilter_CSTATE_j;     // '<S8>/Low Pass Filter'
    real_T Integrator_CSTATE;          // '<S150>/Integrator'
    real_T Filter_CSTATE;              // '<S145>/Filter'
    real_T LowPassFilter_CSTATE_c;     // '<S4>/Low Pass Filter'
    real_T z_CSTATE[2];                // '<Root>/z'
    real_T Integrator_CSTATE_f;        // '<S44>/Integrator'
    real_T Filter_CSTATE_l;            // '<S39>/Filter'
    real_T TransferFcn_CSTATE;         // '<S4>/Transfer Fcn'
    real_T vx_curr_CSTATE;             // '<Root>/vx_curr'
    real_T LowPassFilter_CSTATE_d;     // '<S7>/Low Pass Filter'
    real_T Integrator_CSTATE_k;        // '<S97>/Integrator'
    real_T Filter_CSTATE_n;            // '<S92>/Filter'
  };

  // State derivatives (default storage)
  struct XDot_VisionHelicopter_T {
    real_T PlantPitch_CSTATE[2];       // '<Root>/Plant (Pitch)'
    real_T LowPassFilter_CSTATE;       // '<S5>/Low Pass Filter'
    real_T PlantRoll_CSTATE[2];        // '<Root>/Plant (Roll)'
    real_T LowPassFilter_CSTATE_b;     // '<S6>/Low Pass Filter'
    real_T Integrator1_CSTATE;         // '<Root>/Integrator1'
    real_T LowPassFilter_CSTATE_j;     // '<S8>/Low Pass Filter'
    real_T Integrator_CSTATE;          // '<S150>/Integrator'
    real_T Filter_CSTATE;              // '<S145>/Filter'
    real_T LowPassFilter_CSTATE_c;     // '<S4>/Low Pass Filter'
    real_T z_CSTATE[2];                // '<Root>/z'
    real_T Integrator_CSTATE_f;        // '<S44>/Integrator'
    real_T Filter_CSTATE_l;            // '<S39>/Filter'
    real_T TransferFcn_CSTATE;         // '<S4>/Transfer Fcn'
    real_T vx_curr_CSTATE;             // '<Root>/vx_curr'
    real_T LowPassFilter_CSTATE_d;     // '<S7>/Low Pass Filter'
    real_T Integrator_CSTATE_k;        // '<S97>/Integrator'
    real_T Filter_CSTATE_n;            // '<S92>/Filter'
  };

  // State disabled
  struct XDis_VisionHelicopter_T {
    boolean_T PlantPitch_CSTATE[2];    // '<Root>/Plant (Pitch)'
    boolean_T LowPassFilter_CSTATE;    // '<S5>/Low Pass Filter'
    boolean_T PlantRoll_CSTATE[2];     // '<Root>/Plant (Roll)'
    boolean_T LowPassFilter_CSTATE_b;  // '<S6>/Low Pass Filter'
    boolean_T Integrator1_CSTATE;      // '<Root>/Integrator1'
    boolean_T LowPassFilter_CSTATE_j;  // '<S8>/Low Pass Filter'
    boolean_T Integrator_CSTATE;       // '<S150>/Integrator'
    boolean_T Filter_CSTATE;           // '<S145>/Filter'
    boolean_T LowPassFilter_CSTATE_c;  // '<S4>/Low Pass Filter'
    boolean_T z_CSTATE[2];             // '<Root>/z'
    boolean_T Integrator_CSTATE_f;     // '<S44>/Integrator'
    boolean_T Filter_CSTATE_l;         // '<S39>/Filter'
    boolean_T TransferFcn_CSTATE;      // '<S4>/Transfer Fcn'
    boolean_T vx_curr_CSTATE;          // '<Root>/vx_curr'
    boolean_T LowPassFilter_CSTATE_d;  // '<S7>/Low Pass Filter'
    boolean_T Integrator_CSTATE_k;     // '<S97>/Integrator'
    boolean_T Filter_CSTATE_n;         // '<S92>/Filter'
  };

  // Constant parameters (default storage)
  struct ConstP_VisionHelicopter_T {
    // Pooled Parameter (Expression: [0 1; 0 -0.01/0.03125];)
    //  Referenced by:
    //    '<Root>/Plant (Pitch)'
    //    '<Root>/Plant (Roll)'

    real_T pooled1[2];
  };

  // Real-time Model Data Structure
  using odeFSubArray = real_T[20];
  struct RT_MODEL_VisionHelicopter_T {
    const char_T *errorStatus;
    RTWSolverInfo solverInfo;
    X_VisionHelicopter_T *contStates;
    int_T *periodicContStateIndices;
    real_T *periodicContStateRanges;
    real_T *derivs;
    XDis_VisionHelicopter_T *contStateDisabled;
    boolean_T zCCacheNeedsReset;
    boolean_T derivCacheNeedsReset;
    boolean_T CTOutputIncnstWithState;
    real_T odeY[20];
    real_T odeF[3][20];
    ODE3_IntgData intgData;

    //
    //  Sizes:
    //  The following substructure contains sizes information
    //  for many of the model attributes such as inputs, outputs,
    //  dwork, sample times, etc.

    struct {
      int_T numContStates;
      int_T numPeriodicContStates;
      int_T numSampTimes;
    } Sizes;

    //
    //  Timing:
    //  The following substructure contains information regarding
    //  the timing information for the model.

    struct {
      uint32_T clockTick0;
      time_T stepSize0;
      uint32_T clockTick1;
      time_T tStart;
      SimTimeStep simTimeStep;
      boolean_T stopRequestedFlag;
      time_T *t;
      time_T tArray[2];
    } Timing;

    time_T** getTPtrPtr();
    boolean_T getStopRequested() const;
    void setStopRequested(boolean_T aStopRequested);
    const char_T* getErrorStatus() const;
    void setErrorStatus(const char_T* const aErrorStatus);
    time_T* getTPtr() const;
    void setTPtr(time_T* aTPtr);
    boolean_T* getStopRequestedPtr();
    const char_T** getErrorStatusPtr();
    boolean_T isMajorTimeStep() const;
    boolean_T isMinorTimeStep() const;
    time_T getTStart() const;
  };

  // Copy Constructor
  VisionHelicopter(VisionHelicopter const&) = delete;

  // Assignment Operator
  VisionHelicopter& operator= (VisionHelicopter const&) & = delete;

  // Move Constructor
  VisionHelicopter(VisionHelicopter &&) = delete;

  // Move Assignment Operator
  VisionHelicopter& operator= (VisionHelicopter &&) = delete;

  // Real-Time Model get method
  VisionHelicopter::RT_MODEL_VisionHelicopter_T * getRTM();

  // model initialize function
  void initialize();

  // model step function
  void step();

  // model terminate function
  static void terminate();

  // Constructor
  VisionHelicopter();

  // Destructor
  ~VisionHelicopter();

  // private data and function members
 private:
  // Block signals
  B_VisionHelicopter_T VisionHelicopter_B;

  // Block states
  DW_VisionHelicopter_T VisionHelicopter_DW;

  // Block continuous states
  X_VisionHelicopter_T VisionHelicopter_X;

  // Block Continuous state disabled vector
  XDis_VisionHelicopter_T VisionHelicopter_XDis;

  // Global mass matrix

  // Continuous states update member function
  void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si );

  // Derivatives member function
  void VisionHelicopter_derivatives();

  // Real-Time Model
  RT_MODEL_VisionHelicopter_T VisionHelicopter_M;
};

// Constant parameters (default storage)
extern const VisionHelicopter::ConstP_VisionHelicopter_T VisionHelicopter_ConstP;

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S94>/Integral Gain' : Eliminated nontunable gain of 1
//  Block '<S102>/Proportional Gain' : Eliminated nontunable gain of 1
//  Block '<S147>/Integral Gain' : Eliminated nontunable gain of 1
//  Block '<S155>/Proportional Gain' : Eliminated nontunable gain of 1


//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'VisionHelicopter'
//  '<S1>'   : 'VisionHelicopter/MATLAB Function'
//  '<S2>'   : 'VisionHelicopter/MATLAB Function1'
//  '<S3>'   : 'VisionHelicopter/MATLAB Function2'
//  '<S4>'   : 'VisionHelicopter/altitude_ctrl'
//  '<S5>'   : 'VisionHelicopter/pitch_torque_conv'
//  '<S6>'   : 'VisionHelicopter/roll_torque_conv'
//  '<S7>'   : 'VisionHelicopter/velPitch_ctrl'
//  '<S8>'   : 'VisionHelicopter/velRoll_ctrl'
//  '<S9>'   : 'VisionHelicopter/altitude_ctrl/PID Controller'
//  '<S10>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/Anti-windup'
//  '<S11>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/D Gain'
//  '<S12>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/External Derivative'
//  '<S13>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/Filter'
//  '<S14>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/Filter ICs'
//  '<S15>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/I Gain'
//  '<S16>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/Ideal P Gain'
//  '<S17>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/Ideal P Gain Fdbk'
//  '<S18>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/Integrator'
//  '<S19>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/Integrator ICs'
//  '<S20>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/N Copy'
//  '<S21>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/N Gain'
//  '<S22>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/P Copy'
//  '<S23>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/Parallel P Gain'
//  '<S24>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/Reset Signal'
//  '<S25>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/Saturation'
//  '<S26>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/Saturation Fdbk'
//  '<S27>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/Sum'
//  '<S28>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/Sum Fdbk'
//  '<S29>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/Tracking Mode'
//  '<S30>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/Tracking Mode Sum'
//  '<S31>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/Tsamp - Integral'
//  '<S32>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/Tsamp - Ngain'
//  '<S33>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/postSat Signal'
//  '<S34>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/preInt Signal'
//  '<S35>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/preSat Signal'
//  '<S36>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/Anti-windup/Passthrough'
//  '<S37>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/D Gain/Internal Parameters'
//  '<S38>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/External Derivative/Error'
//  '<S39>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/Filter/Cont. Filter'
//  '<S40>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S41>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/I Gain/Internal Parameters'
//  '<S42>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/Ideal P Gain/Passthrough'
//  '<S43>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S44>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/Integrator/Continuous'
//  '<S45>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/Integrator ICs/Internal IC'
//  '<S46>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/N Copy/Disabled'
//  '<S47>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/N Gain/Internal Parameters'
//  '<S48>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/P Copy/Disabled'
//  '<S49>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/Parallel P Gain/Internal Parameters'
//  '<S50>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/Reset Signal/Disabled'
//  '<S51>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/Saturation/Passthrough'
//  '<S52>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/Saturation Fdbk/Disabled'
//  '<S53>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/Sum/Sum_PID'
//  '<S54>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/Sum Fdbk/Disabled'
//  '<S55>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/Tracking Mode/Disabled'
//  '<S56>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S57>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S58>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S59>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/postSat Signal/Forward_Path'
//  '<S60>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/preInt Signal/Internal PreInt'
//  '<S61>'  : 'VisionHelicopter/altitude_ctrl/PID Controller/preSat Signal/Forward_Path'
//  '<S62>'  : 'VisionHelicopter/velPitch_ctrl/PID Controller'
//  '<S63>'  : 'VisionHelicopter/velPitch_ctrl/PID Controller/Anti-windup'
//  '<S64>'  : 'VisionHelicopter/velPitch_ctrl/PID Controller/D Gain'
//  '<S65>'  : 'VisionHelicopter/velPitch_ctrl/PID Controller/External Derivative'
//  '<S66>'  : 'VisionHelicopter/velPitch_ctrl/PID Controller/Filter'
//  '<S67>'  : 'VisionHelicopter/velPitch_ctrl/PID Controller/Filter ICs'
//  '<S68>'  : 'VisionHelicopter/velPitch_ctrl/PID Controller/I Gain'
//  '<S69>'  : 'VisionHelicopter/velPitch_ctrl/PID Controller/Ideal P Gain'
//  '<S70>'  : 'VisionHelicopter/velPitch_ctrl/PID Controller/Ideal P Gain Fdbk'
//  '<S71>'  : 'VisionHelicopter/velPitch_ctrl/PID Controller/Integrator'
//  '<S72>'  : 'VisionHelicopter/velPitch_ctrl/PID Controller/Integrator ICs'
//  '<S73>'  : 'VisionHelicopter/velPitch_ctrl/PID Controller/N Copy'
//  '<S74>'  : 'VisionHelicopter/velPitch_ctrl/PID Controller/N Gain'
//  '<S75>'  : 'VisionHelicopter/velPitch_ctrl/PID Controller/P Copy'
//  '<S76>'  : 'VisionHelicopter/velPitch_ctrl/PID Controller/Parallel P Gain'
//  '<S77>'  : 'VisionHelicopter/velPitch_ctrl/PID Controller/Reset Signal'
//  '<S78>'  : 'VisionHelicopter/velPitch_ctrl/PID Controller/Saturation'
//  '<S79>'  : 'VisionHelicopter/velPitch_ctrl/PID Controller/Saturation Fdbk'
//  '<S80>'  : 'VisionHelicopter/velPitch_ctrl/PID Controller/Sum'
//  '<S81>'  : 'VisionHelicopter/velPitch_ctrl/PID Controller/Sum Fdbk'
//  '<S82>'  : 'VisionHelicopter/velPitch_ctrl/PID Controller/Tracking Mode'
//  '<S83>'  : 'VisionHelicopter/velPitch_ctrl/PID Controller/Tracking Mode Sum'
//  '<S84>'  : 'VisionHelicopter/velPitch_ctrl/PID Controller/Tsamp - Integral'
//  '<S85>'  : 'VisionHelicopter/velPitch_ctrl/PID Controller/Tsamp - Ngain'
//  '<S86>'  : 'VisionHelicopter/velPitch_ctrl/PID Controller/postSat Signal'
//  '<S87>'  : 'VisionHelicopter/velPitch_ctrl/PID Controller/preInt Signal'
//  '<S88>'  : 'VisionHelicopter/velPitch_ctrl/PID Controller/preSat Signal'
//  '<S89>'  : 'VisionHelicopter/velPitch_ctrl/PID Controller/Anti-windup/Passthrough'
//  '<S90>'  : 'VisionHelicopter/velPitch_ctrl/PID Controller/D Gain/Internal Parameters'
//  '<S91>'  : 'VisionHelicopter/velPitch_ctrl/PID Controller/External Derivative/Error'
//  '<S92>'  : 'VisionHelicopter/velPitch_ctrl/PID Controller/Filter/Cont. Filter'
//  '<S93>'  : 'VisionHelicopter/velPitch_ctrl/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S94>'  : 'VisionHelicopter/velPitch_ctrl/PID Controller/I Gain/Internal Parameters'
//  '<S95>'  : 'VisionHelicopter/velPitch_ctrl/PID Controller/Ideal P Gain/Passthrough'
//  '<S96>'  : 'VisionHelicopter/velPitch_ctrl/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S97>'  : 'VisionHelicopter/velPitch_ctrl/PID Controller/Integrator/Continuous'
//  '<S98>'  : 'VisionHelicopter/velPitch_ctrl/PID Controller/Integrator ICs/Internal IC'
//  '<S99>'  : 'VisionHelicopter/velPitch_ctrl/PID Controller/N Copy/Disabled'
//  '<S100>' : 'VisionHelicopter/velPitch_ctrl/PID Controller/N Gain/Internal Parameters'
//  '<S101>' : 'VisionHelicopter/velPitch_ctrl/PID Controller/P Copy/Disabled'
//  '<S102>' : 'VisionHelicopter/velPitch_ctrl/PID Controller/Parallel P Gain/Internal Parameters'
//  '<S103>' : 'VisionHelicopter/velPitch_ctrl/PID Controller/Reset Signal/Disabled'
//  '<S104>' : 'VisionHelicopter/velPitch_ctrl/PID Controller/Saturation/Passthrough'
//  '<S105>' : 'VisionHelicopter/velPitch_ctrl/PID Controller/Saturation Fdbk/Disabled'
//  '<S106>' : 'VisionHelicopter/velPitch_ctrl/PID Controller/Sum/Sum_PID'
//  '<S107>' : 'VisionHelicopter/velPitch_ctrl/PID Controller/Sum Fdbk/Disabled'
//  '<S108>' : 'VisionHelicopter/velPitch_ctrl/PID Controller/Tracking Mode/Disabled'
//  '<S109>' : 'VisionHelicopter/velPitch_ctrl/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S110>' : 'VisionHelicopter/velPitch_ctrl/PID Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S111>' : 'VisionHelicopter/velPitch_ctrl/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S112>' : 'VisionHelicopter/velPitch_ctrl/PID Controller/postSat Signal/Forward_Path'
//  '<S113>' : 'VisionHelicopter/velPitch_ctrl/PID Controller/preInt Signal/Internal PreInt'
//  '<S114>' : 'VisionHelicopter/velPitch_ctrl/PID Controller/preSat Signal/Forward_Path'
//  '<S115>' : 'VisionHelicopter/velRoll_ctrl/PID Controller'
//  '<S116>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/Anti-windup'
//  '<S117>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/D Gain'
//  '<S118>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/External Derivative'
//  '<S119>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/Filter'
//  '<S120>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/Filter ICs'
//  '<S121>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/I Gain'
//  '<S122>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/Ideal P Gain'
//  '<S123>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/Ideal P Gain Fdbk'
//  '<S124>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/Integrator'
//  '<S125>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/Integrator ICs'
//  '<S126>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/N Copy'
//  '<S127>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/N Gain'
//  '<S128>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/P Copy'
//  '<S129>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/Parallel P Gain'
//  '<S130>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/Reset Signal'
//  '<S131>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/Saturation'
//  '<S132>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/Saturation Fdbk'
//  '<S133>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/Sum'
//  '<S134>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/Sum Fdbk'
//  '<S135>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/Tracking Mode'
//  '<S136>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/Tracking Mode Sum'
//  '<S137>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/Tsamp - Integral'
//  '<S138>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/Tsamp - Ngain'
//  '<S139>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/postSat Signal'
//  '<S140>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/preInt Signal'
//  '<S141>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/preSat Signal'
//  '<S142>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/Anti-windup/Passthrough'
//  '<S143>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/D Gain/Internal Parameters'
//  '<S144>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/External Derivative/Error'
//  '<S145>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/Filter/Cont. Filter'
//  '<S146>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/Filter ICs/Internal IC - Filter'
//  '<S147>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/I Gain/Internal Parameters'
//  '<S148>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/Ideal P Gain/Passthrough'
//  '<S149>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/Ideal P Gain Fdbk/Disabled'
//  '<S150>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/Integrator/Continuous'
//  '<S151>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/Integrator ICs/Internal IC'
//  '<S152>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/N Copy/Disabled'
//  '<S153>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/N Gain/Internal Parameters'
//  '<S154>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/P Copy/Disabled'
//  '<S155>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/Parallel P Gain/Internal Parameters'
//  '<S156>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/Reset Signal/Disabled'
//  '<S157>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/Saturation/Passthrough'
//  '<S158>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/Saturation Fdbk/Disabled'
//  '<S159>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/Sum/Sum_PID'
//  '<S160>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/Sum Fdbk/Disabled'
//  '<S161>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/Tracking Mode/Disabled'
//  '<S162>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/Tracking Mode Sum/Passthrough'
//  '<S163>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/Tsamp - Integral/TsSignalSpecification'
//  '<S164>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/Tsamp - Ngain/Passthrough'
//  '<S165>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/postSat Signal/Forward_Path'
//  '<S166>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/preInt Signal/Internal PreInt'
//  '<S167>' : 'VisionHelicopter/velRoll_ctrl/PID Controller/preSat Signal/Forward_Path'

#endif                                 // VisionHelicopter_h_

//
// File trailer for generated code.
//
// [EOF]
//
