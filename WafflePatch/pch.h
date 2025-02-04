#ifndef PCH_H
#define PCH_H

//#define PROTECTED_EXE

#include "framework.h"
#include "Hijacker.h"
#include "DetoursHelper.h"
#include "LoadLibHooker.h"
#ifdef PROTECTED_EXE
#include "Pe.h"
#endif

#include "Log.h"
#ifdef PROTECTED_EXE
#include "MemoryUtil.h"
#endif

#include "WaffleInjector.h"
#include "WafflePatcher.h"

#endif //PCH_H
