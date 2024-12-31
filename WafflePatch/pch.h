#ifndef PCH_H
#define PCH_H

#include "framework.h"
#include "Hijacker.h"
#include "DetoursHelper.h"
#include "LoadLibHooker.h"
#include "Common.h"
#ifdef PROTECTED_EXE
#include "Pe.h"
#endif // PROTECTED_EXE

#include "WaffleInjector.h"
#include "WafflePatcher.h"

#endif //PCH_H
