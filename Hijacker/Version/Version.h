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
    static inline PVOID OriginalGetFileVersionInfoA;
    static inline PVOID OriginalGetFileVersionInfoByHandle;
    static inline PVOID OriginalGetFileVersionInfoExA;
    static inline PVOID OriginalGetFileVersionInfoExW;
    static inline PVOID OriginalGetFileVersionInfoSizeA;
    static inline PVOID OriginalGetFileVersionInfoSizeExA;
    static inline PVOID OriginalGetFileVersionInfoSizeExW;
    static inline PVOID OriginalGetFileVersionInfoSizeW;
    static inline PVOID OriginalGetFileVersionInfoW;
    static inline PVOID OriginalVerFindFileA;
    static inline PVOID OriginalVerFindFileW;
    static inline PVOID OriginalVerInstallFileA;
    static inline PVOID OriginalVerInstallFileW;
    static inline PVOID OriginalVerLanguageNameA;
    static inline PVOID OriginalVerLanguageNameW;
    static inline PVOID OriginalVerQueryValueA;
    static inline PVOID OriginalVerQueryValueW;
};

#endif
