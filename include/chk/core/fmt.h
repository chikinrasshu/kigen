#pragma once

#include <chk/core/api.h>

#include <chk/core/types.h>

CORE_API B8 Str_FmtF(Str buf, Size bufSize, CStr fmt, ...);
CORE_API B8 Str_FmtV(Str buf, Size bufSize, CStr fmt, Args args);
