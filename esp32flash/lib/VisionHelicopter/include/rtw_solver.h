/*
 * rtw_solver.h - Minimal stub for Simulink ERT solver info.
 * Provides the RTWSolverInfo struct and all required rtsi* macros
 * so VisionHelicopter (ERT target, ODE3) compiles on ESP32.
 */
#ifndef RTW_SOLVER_H
#define RTW_SOLVER_H

#include "rtwtypes.h"

/*
 * SimTimeStep enum – MUST be an enum, not a macro, because the
 * generated RT_MODEL_...::isMajorTimeStep() does:
 *   return ((Timing.simTimeStep) == MAJOR_TIME_STEP);
 */
typedef enum {
  MAJOR_TIME_STEP = 0,
  MINOR_TIME_STEP = 1
} SimTimeStep;

/*
 * RTWSolverInfo – All fields actually written/read by the generated
 * initialize() and step() code and the ODE3 integrator.
 */
typedef struct {
  /* Pointers stored by rtsiSet*Ptr macros */
  SimTimeStep  *simTimeStepPtr;
  time_T      **tPtr;
  time_T       *stepSizePtr;
  real_T      **dXPtr;
  real_T      **contStatesPtr;
  int_T        *numContStatesPtr;
  int_T        *numPeriodicContStatesPtr;
  int_T       **periodicContStateIndicesPtr;
  real_T      **periodicContStateRangesPtr;
  boolean_T  **contStateDisabledPtr;
  const char_T **errorStatusPtr;
  void          *RTModelPtr;

  /* Solver working data (set directly by initialize) */
  void          *solverData;   /* ODE3_IntgData* */
  const char_T  *solverName;
  time_T         solverStopTime;

  /* Minor-time-step flags */
  boolean_T      isMinorTimeStepWithModeChange;
  boolean_T      isContModeFrozen;
} RTWSolverInfo;

/* ---- Ptr setters ---- */
#define rtsiSetSimTimeStepPtr(S,v)           ((S)->simTimeStepPtr = (v))
#define rtsiSetTPtr(S,v)                     ((S)->tPtr = (v))
#define rtsiSetStepSizePtr(S,v)              ((S)->stepSizePtr = (v))
#define rtsiSetdXPtr(S,v)                    ((S)->dXPtr = (v))
#define rtsiSetContStatesPtr(S,v)            ((S)->contStatesPtr = (v))
#define rtsiSetNumContStatesPtr(S,v)         ((S)->numContStatesPtr = (v))
#define rtsiSetNumPeriodicContStatesPtr(S,v) ((S)->numPeriodicContStatesPtr = (v))
#define rtsiSetPeriodicContStateIndicesPtr(S,v) ((S)->periodicContStateIndicesPtr = (v))
#define rtsiSetPeriodicContStateRangesPtr(S,v)  ((S)->periodicContStateRangesPtr = (v))
#define rtsiSetContStateDisabledPtr(S,v)     ((S)->contStateDisabledPtr = (v))
#define rtsiSetErrorStatusPtr(S,v)           ((S)->errorStatusPtr = (v))
#define rtsiSetRTModelPtr(S,v)               ((S)->RTModelPtr = (void*)(v))

/* ---- Solver data / name ---- */
#define rtsiSetSolverData(S,v)    ((S)->solverData = (v))
#define rtsiGetSolverData(S)      ((S)->solverData)
#define rtsiSetSolverName(S,v)    ((S)->solverName = (v))

/* ---- SimTimeStep ---- */
#define rtsiSetSimTimeStep(S,v)   (*(S)->simTimeStepPtr = (v))
#define rtsiGetSimTimeStep(S)     (*(S)->simTimeStepPtr)

/* ---- Time access through pointers ---- */
#define rtsiGetT(S)               (**(S)->tPtr)
#define rtsiSetT(S,v)             (**(S)->tPtr = (v))
#define rtsiGetStepSize(S)        (*(S)->stepSizePtr)

/* ---- Solver stop time ---- */
#define rtsiSetSolverStopTime(S,v) ((S)->solverStopTime = (v))
#define rtsiGetSolverStopTime(S)   ((S)->solverStopTime)

/* ---- Continuous states & derivatives ---- */
#define rtsiGetContStates(S)      (*(S)->contStatesPtr)
#define rtsiSetdX(S,v)            (*(S)->dXPtr = (v))

/* ---- Mode-update flag ---- */
#define rtsiSetIsMinorTimeStepWithModeChange(S,v) ((S)->isMinorTimeStepWithModeChange = (v))
#define rtsiSetIsContModeFrozen(S,v)              ((S)->isContModeFrozen = (v))
#define rtsiIsModeUpdateTimeStep(S)               (true)

#endif /* RTW_SOLVER_H */
