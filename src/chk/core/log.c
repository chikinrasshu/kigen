#include <chk/core/log.h>

#include <chk/core/fmt.h>

#include <cwalk.h>

#include <stdio.h>

CORE_LOCAL static LogLv g_logLevel = LogLv_Info;
CORE_LOCAL static LogFn g_logFn    = _LogS;
CORE_LOCAL static Ptr   g_logData  = NULL;

CORE_API CStr LogLv_ToStr(LogLv lv) {
  switch (lv) {
    case LogLv_None:
    case LogLv_Count: break;

    case LogLv_Trace: return "Trace";
    case LogLv_Debug: return "Debug";
    case LogLv_Info:  return "Info";
    case LogLv_Warn:  return "Warn";
    case LogLv_Error: return "Error";
    case LogLv_Fatal: return "Fatal";
  }

  return "Unknown";
}

CORE_API LogLv Log_SetLevel(LogLv lv) {
  LogLv prev = g_logLevel;
  g_logLevel = lv;

  return prev;
}

CORE_API LogLv Log_GetLevel(void) {
  LogLv lv = g_logLevel;

  return lv;
}

CORE_API LogFn Log_SetFn(LogFn fn) {
  LogFn prev = g_logFn;
  g_logFn    = fn;

  return prev;
}

CORE_API LogFn Log_GetFn(void) {
  LogFn fn = g_logFn;

  return fn;
}

CORE_API Ptr Log_SetData(Ptr data) {
  Ptr prev  = g_logData;
  g_logData = data;

  return prev;
}

CORE_API Ptr Log_GetData(void) {
  Ptr data = g_logData;

  return data;
}

CORE_API B8 _Log(LogLv lv, CStr msg, CStr f, U32 ln, CStr fn) {
  B8 result = false;

  LogFn logFn = Log_GetFn();
  if (logFn) {
    Ptr logData = Log_GetData();

    struct cwk_segment seg;
    if (cwk_path_get_last_segment(f, &seg)) { f = seg.begin; }

    result = logFn(lv, msg, f, ln, fn, logData);
  } else {
    result = true;
  }

  return result;
}

CORE_API B8 _LogF(LogLv lv, CStr fmt, CStr f, U32 ln, CStr fn, ...) {
  B8 result = false;

  Args args;
  Args_Init(args, fn);
  result = _LogV(lv, fmt, f, ln, fn, args);
  Args_Destroy(args);

  return result;
}

CORE_API B8 _LogV(LogLv lv, CStr fmt, CStr f, U32 ln, CStr fn, Args args) {
  B8 result = false;

  C8 buf[256];

  Args argsCopy;
  Args_Copy(argsCopy, args);
  if (Str_FmtV(buf, SizeOf(buf), fmt, argsCopy)) {
    result = _Log(lv, buf, f, ln, fn);
  } else {
    result = _Log(lv, fmt, f, ln, fn);
  }
  Args_Destroy(argsCopy);

  return result;
}

CORE_API B8 _LogS(LogLv lv, CStr msg, CStr f, U32 ln, CStr fn, Ptr data) {
  (void)data;

  B8 result = false;

  if (lv >= Log_GetLevel()) {
    CStr lvStr = LogLv_ToStr(lv);
    CStr fmt   = "[%s] [%s:%u:%s] %s\n";

    FILE* stream  = (lv >= LogLv_Error) ? stderr : stdout;
    S32   written = fprintf(stream, fmt, lvStr, f, ln, fn, msg);
    result        = written > 0;
  }

  return result;
}
