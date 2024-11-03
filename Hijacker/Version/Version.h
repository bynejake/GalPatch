#pragma once

#ifdef VERSION

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include "Core/Core.h"

class Hijacker final : Core
{
public:
    static void Hijack  (LPCTSTR lpSrc);
    static void Release ();

private:
    DECLARE_ORIGINAL_FUNC(GetFileVersionInfoA)
    DECLARE_ORIGINAL_FUNC(GetFileVersionInfoByHandle)
    DECLARE_ORIGINAL_FUNC(GetFileVersionInfoExA)
    DECLARE_ORIGINAL_FUNC(GetFileVersionInfoExW)
    DECLARE_ORIGINAL_FUNC(GetFileVersionInfoSizeA)
    DECLARE_ORIGINAL_FUNC(GetFileVersionInfoSizeExA)
    DECLARE_ORIGINAL_FUNC(GetFileVersionInfoSizeExW)
    DECLARE_ORIGINAL_FUNC(GetFileVersionInfoSizeW)
    DECLARE_ORIGINAL_FUNC(GetFileVersionInfoW)
    DECLARE_ORIGINAL_FUNC(VerFindFileA)
    DECLARE_ORIGINAL_FUNC(VerFindFileW)
    DECLARE_ORIGINAL_FUNC(VerInstallFileA)
    DECLARE_ORIGINAL_FUNC(VerInstallFileW)
    DECLARE_ORIGINAL_FUNC(VerLanguageNameA)
    DECLARE_ORIGINAL_FUNC(VerLanguageNameW)
    DECLARE_ORIGINAL_FUNC(VerQueryValueA)
    DECLARE_ORIGINAL_FUNC(VerQueryValueW)
};

#endif
