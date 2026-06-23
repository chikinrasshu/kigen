#include <chk/core/fmt.h>

#include <stdio.h>

CORE_API B8 Str_FmtF(Str buf, Size bufSize, CStr fmt, ...) {
  B8 result = false;

  Args args;
  Args_Init(args, fmt);
  result = Str_FmtV(buf, bufSize, fmt, args);
  Args_Destroy(args);

  return result;
}

CORE_API B8 Str_FmtV(Str buf, Size bufSize, CStr fmt, Args args) {
  B8 result = false;

  Args argsCopy;
  Args_Copy(argsCopy, args);
  Size len = vsnprintf(buf, bufSize, fmt, args);
  result   = (len > 0 && (Size)len < bufSize);
  Args_Destroy(argsCopy);

  return result;
}
