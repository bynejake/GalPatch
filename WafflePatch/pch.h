#ifndef PCH_H
#define PCH_H

//#define KANIN

#if defined(KANIN)
#define PROTECTED_EXE
#endif

#include "framework.h"
#include "Hijacker.h"
#include "DetoursHelper.h"
#include "LoadLibHooker.h"
#include "Common.h"
#ifdef PROTECTED_EXE
#include "Pe.h"
#endif

#include "WaffleInjector.h"
#include "WafflePatcher.h"

#endif //PCH_H
