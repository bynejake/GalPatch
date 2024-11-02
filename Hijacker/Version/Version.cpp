#ifdef VERSION

#include "Version.h"

void Hijacker::Hijack(LPCWSTR lpSrc)
{
    Core::Hijack(L"version.dll", lpSrc);

    RESOLVE_ORIGINAL_FUNC(GetFileVersionInfoA)
    RESOLVE_ORIGINAL_FUNC(GetFileVersionInfoByHandle)
    RESOLVE_ORIGINAL_FUNC(GetFileVersionInfoExA)
    RESOLVE_ORIGINAL_FUNC(GetFileVersionInfoExW)
    RESOLVE_ORIGINAL_FUNC(GetFileVersionInfoSizeA)
    RESOLVE_ORIGINAL_FUNC(GetFileVersionInfoSizeExA)
    RESOLVE_ORIGINAL_FUNC(GetFileVersionInfoSizeExW)
    RESOLVE_ORIGINAL_FUNC(GetFileVersionInfoSizeW)
    RESOLVE_ORIGINAL_FUNC(GetFileVersionInfoW)
    RESOLVE_ORIGINAL_FUNC(VerFindFileA)
    RESOLVE_ORIGINAL_FUNC(VerFindFileW)
    RESOLVE_ORIGINAL_FUNC(VerInstallFileA)
    RESOLVE_ORIGINAL_FUNC(VerInstallFileW)
    RESOLVE_ORIGINAL_FUNC(VerLanguageNameA)
    RESOLVE_ORIGINAL_FUNC(VerLanguageNameW)
    RESOLVE_ORIGINAL_FUNC(VerQueryValueA)
    RESOLVE_ORIGINAL_FUNC(VerQueryValueW)
}

void Hijacker::Release()
{
    Core::Release();
}

DECLARE_FAKE_FUNC(GetFileVersionInfoA)
DECLARE_FAKE_FUNC(GetFileVersionInfoByHandle)
DECLARE_FAKE_FUNC(GetFileVersionInfoExA)
DECLARE_FAKE_FUNC(GetFileVersionInfoExW)
DECLARE_FAKE_FUNC(GetFileVersionInfoSizeA)
DECLARE_FAKE_FUNC(GetFileVersionInfoSizeExA)
DECLARE_FAKE_FUNC(GetFileVersionInfoSizeExW)
DECLARE_FAKE_FUNC(GetFileVersionInfoSizeW)
DECLARE_FAKE_FUNC(GetFileVersionInfoW)
DECLARE_FAKE_FUNC(VerFindFileA)
DECLARE_FAKE_FUNC(VerFindFileW)
DECLARE_FAKE_FUNC(VerInstallFileA)
DECLARE_FAKE_FUNC(VerInstallFileW)
DECLARE_FAKE_FUNC(VerLanguageNameA)
DECLARE_FAKE_FUNC(VerLanguageNameW)
DECLARE_FAKE_FUNC(VerQueryValueA)
DECLARE_FAKE_FUNC(VerQueryValueW)

EXPORT_FAKE_FUNC(GetFileVersionInfoA, 1)
EXPORT_FAKE_FUNC(GetFileVersionInfoByHandle, 2)
EXPORT_FAKE_FUNC(GetFileVersionInfoExA, 3)
EXPORT_FAKE_FUNC(GetFileVersionInfoExW, 4)
EXPORT_FAKE_FUNC(GetFileVersionInfoSizeA, 5)
EXPORT_FAKE_FUNC(GetFileVersionInfoSizeExA, 6)
EXPORT_FAKE_FUNC(GetFileVersionInfoSizeExW, 7)
EXPORT_FAKE_FUNC(GetFileVersionInfoSizeW, 8)
EXPORT_FAKE_FUNC(GetFileVersionInfoW, 9)
EXPORT_FAKE_FUNC(VerFindFileA, 10)
EXPORT_FAKE_FUNC(VerFindFileW, 11)
EXPORT_FAKE_FUNC(VerInstallFileA, 12)
EXPORT_FAKE_FUNC(VerInstallFileW, 13)
EXPORT_FAKE_FUNC(VerLanguageNameA, 14)
EXPORT_FAKE_FUNC(VerLanguageNameW, 15)
EXPORT_FAKE_FUNC(VerQueryValueA, 16)
EXPORT_FAKE_FUNC(VerQueryValueW, 17)

#endif
