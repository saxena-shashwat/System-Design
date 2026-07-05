#ifndef RT_LOGGING_H
#define RT_LOGGING_H

typedef struct { void* loggingInterval; } RTWLogInfo;

#define rt_UpdateTXYLogVars(S, val)
#define rtliSetLogXSignalInfo(S, val)
#define rtliSetLogXSignalPtrs(S, val)
#define rtliSetLogT(S, val)
#define rtliSetLogX(S, val)
#define rtliSetLogXFinal(S, val)
#define rtliSetLogVarNameModifier(S, val)
#define rtliSetLogFormat(S, val)
#define rtliSetLogMaxRows(S, val)
#define rtliSetLogDecimation(S, val)
#define rtliSetLogY(S, val)
#define rtliSetLogYSignalInfo(S, val)
#define rtliSetLogYSignalPtrs(S, val)
#define rt_StartDataLoggingWithStartTime(S, val, val2, val3, val4)

#endif
