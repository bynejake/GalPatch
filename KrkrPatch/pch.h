#ifndef PCH_H
#define PCH_H

#include "framework.h"
#include "Hijacker.h"
#include "DetoursHelper.h"
#include "LoadLibHooker.h"
#include "PE.h"
#include "CompilerHelper.h"
#include "Common.h"
#include "tp_stub.h"

#ifdef _DEBUG
#include "KrkrLogger.h"
#endif

#include "KrkrInjector.h"
#include "KrkrDefinitions.h"
#include "KrkrPatchArcStream.h"
#include "KrkrPatcher.h"

#endif //PCH_H
