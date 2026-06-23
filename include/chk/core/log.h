#pragma once

#include <chk/core/api.h>

#include <chk/core/types.h>

typedef enum LogLv {
  LogLv_None = 0,

  LogLv_Trace,
  LogLv_Debug,
  LogLv_Info,
  LogLv_Warn,
  LogLv_Error,
  LogLv_Fatal,

  LogLv_Count,
} LogLv;

CORE_API CStr LogLv_ToStr(LogLv lv);

typedef B8 (*LogFn)(LogLv lv, CStr msg, CStr f, U32 ln, CStr fn, Ptr data);

CORE_API LogLv Log_SetLevel(LogLv lv);
CORE_API LogLv Log_GetLevel(void);

CORE_API LogFn Log_SetFn(LogFn fn);
CORE_API LogFn Log_GetFn(void);

CORE_API Ptr Log_SetData(Ptr data);
CORE_API Ptr Log_GetData(void);

CORE_API B8 _Log(LogLv lv, CStr msg, CStr f, U32 ln, CStr fn);
CORE_API B8 _LogF(LogLv lv, CStr fmt, CStr f, U32 ln, CStr fn, ...);
CORE_API B8 _LogV(LogLv lv, CStr fmt, CStr f, U32 ln, CStr fn, Args args);
CORE_API B8 _LogS(LogLv lv, CStr msg, CStr f, U32 ln, CStr fn, Ptr data);

#define Log_Trace(msg, ...)                                                                                            \
  _Log##__VA_OPT__(F)(LogLv_Trace, (msg), __FILE__, __LINE__, __func__ __VA_OPT__(, __VA_ARGS__))
#define Log_Debug(msg, ...)                                                                                            \
  _Log##__VA_OPT__(F)(LogLv_Debug, (msg), __FILE__, __LINE__, __func__ __VA_OPT__(, __VA_ARGS__))
#define Log_Info(msg, ...)                                                                                             \
  _Log##__VA_OPT__(F)(LogLv_Info, (msg), __FILE__, __LINE__, __func__ __VA_OPT__(, __VA_ARGS__))
#define Log_Warn(msg, ...)                                                                                             \
  _Log##__VA_OPT__(F)(LogLv_Warn, (msg), __FILE__, __LINE__, __func__ __VA_OPT__(, __VA_ARGS__))
#define Log_Error(msg, ...)                                                                                            \
  _Log##__VA_OPT__(F)(LogLv_Error, (msg), __FILE__, __LINE__, __func__ __VA_OPT__(, __VA_ARGS__))
#define Log_Fatal(msg, ...)                                                                                            \
  _Log##__VA_OPT__(F)(LogLv_Fatal, (msg), __FILE__, __LINE__, __func__ __VA_OPT__(, __VA_ARGS__))

#define Log_TraceV(fmt, args) _LogV(LogLv_Trace, (fmt), __FILE__, __LINE__, __func__, (args))
#define Log_DebugV(fmt, args) _LogV(LogLv_Debug, (fmt), __FILE__, __LINE__, __func__, (args))
#define Log_InfoV(fmt, args)  _LogV(LogLv_Info, (fmt), __FILE__, __LINE__, __func__, (args))
#define Log_WarnV(fmt, args)  _LogV(LogLv_Warn, (fmt), __FILE__, __LINE__, __func__, (args))
#define Log_ErrorV(fmt, args) _LogV(LogLv_Error, (fmt), __FILE__, __LINE__, __func__, (args))
#define Log_FatalV(fmt, args) _LogV(LogLv_Fatal, (fmt), __FILE__, __LINE__, __func__, (args))
