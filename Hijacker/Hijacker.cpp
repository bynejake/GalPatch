#include <tchar.h>
#include "Hijacker.h"

void Hijacker::Hijack(LPCTSTR lpSrc)
{
    if (RealDll != nullptr)
        return;

    TCHAR realDllPath[MAX_PATH];
    GetSystemDirectory(realDllPath, MAX_PATH);
    _tcscat_s(realDllPath, _T("\\version.dll"));

    RealDll = LoadLibrary(realDllPath);
    if (RealDll == nullptr)
    {
        MessageBox(nullptr, _T("Cannot load Original version.dll library"), lpSrc, MB_ICONERROR);
        ExitProcess(0);
    }

#define RESOLVE(fn) Original##fn = reinterpret_cast<decltype(Original##fn)>(GetProcAddress(RealDll, #fn))
    RESOLVE(GetFileVersionInfoA);
    RESOLVE(GetFileVersionInfoByHandle);
    RESOLVE(GetFileVersionInfoExA);
    RESOLVE(GetFileVersionInfoExW);
    RESOLVE(GetFileVersionInfoSizeA);
    RESOLVE(GetFileVersionInfoSizeExA);
    RESOLVE(GetFileVersionInfoSizeExW);
    RESOLVE(GetFileVersionInfoSizeW);
    RESOLVE(GetFileVersionInfoW);
    RESOLVE(VerFindFileA);
    RESOLVE(VerFindFileW);
    RESOLVE(VerInstallFileA);
    RESOLVE(VerInstallFileW);
    RESOLVE(VerLanguageNameA);
    RESOLVE(VerLanguageNameW);
    RESOLVE(VerQueryValueA);
    RESOLVE(VerQueryValueW);
#undef RESOLVE
}

void Hijacker::Release()
{
    if (RealDll == nullptr)
        return;

    FreeLibrary(RealDll);
    RealDll = nullptr;
}

EXTERN_C _declspec(naked) void FakeGetFileVersionInfoA()        { __asm { jmp[Hijacker::OriginalGetFileVersionInfoA] } }
EXTERN_C _declspec(naked) void FakeGetFileVersionInfoByHandle() { __asm { jmp[Hijacker::OriginalGetFileVersionInfoByHandle] } }
EXTERN_C _declspec(naked) void FakeGetFileVersionInfoExA()      { __asm { jmp[Hijacker::OriginalGetFileVersionInfoExA] } }
EXTERN_C _declspec(naked) void FakeGetFileVersionInfoExW()      { __asm { jmp[Hijacker::OriginalGetFileVersionInfoExW] } }
EXTERN_C _declspec(naked) void FakeGetFileVersionInfoSizeA()    { __asm { jmp[Hijacker::OriginalGetFileVersionInfoSizeA] } }
EXTERN_C _declspec(naked) void FakeGetFileVersionInfoSizeExA()  { __asm { jmp[Hijacker::OriginalGetFileVersionInfoSizeExA] } }
EXTERN_C _declspec(naked) void FakeGetFileVersionInfoSizeExW()  { __asm { jmp[Hijacker::OriginalGetFileVersionInfoSizeExW] } }
EXTERN_C _declspec(naked) void FakeGetFileVersionInfoSizeW()    { __asm { jmp[Hijacker::OriginalGetFileVersionInfoSizeW] } }
EXTERN_C _declspec(naked) void FakeGetFileVersionInfoW()        { __asm { jmp[Hijacker::OriginalGetFileVersionInfoW] } }
EXTERN_C _declspec(naked) void FakeVerFindFileA()               { __asm { jmp[Hijacker::OriginalVerFindFileA] } }
EXTERN_C _declspec(naked) void FakeVerFindFileW()               { __asm { jmp[Hijacker::OriginalVerFindFileW] } }
EXTERN_C _declspec(naked) void FakeVerInstallFileA()            { __asm { jmp[Hijacker::OriginalVerInstallFileA] } }
EXTERN_C _declspec(naked) void FakeVerInstallFileW()            { __asm { jmp[Hijacker::OriginalVerInstallFileW] } }
EXTERN_C _declspec(naked) void FakeVerLanguageNameA()           { __asm { jmp[Hijacker::OriginalVerLanguageNameA] } }
EXTERN_C _declspec(naked) void FakeVerLanguageNameW()           { __asm { jmp[Hijacker::OriginalVerLanguageNameW] } }
EXTERN_C _declspec(naked) void FakeVerQueryValueA()             { __asm { jmp[Hijacker::OriginalVerQueryValueA] } }
EXTERN_C _declspec(naked) void FakeVerQueryValueW()             { __asm { jmp[Hijacker::OriginalVerQueryValueW] } }

#pragma comment(linker, "/EXPORT:GetFileVersionInfoA=_FakeGetFileVersionInfoA,@1")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoByHandle=_FakeGetFileVersionInfoByHandle,@2")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoExA=_FakeGetFileVersionInfoExA,@3")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoExW=_FakeGetFileVersionInfoExW,@4")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeA=_FakeGetFileVersionInfoSizeA,@5")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeExA=_FakeGetFileVersionInfoSizeExA,@6")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeExW=_FakeGetFileVersionInfoSizeExW,@7")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeW=_FakeGetFileVersionInfoSizeW,@8")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoW=_FakeGetFileVersionInfoW,@9")
#pragma comment(linker, "/EXPORT:VerFindFileA=_FakeVerFindFileA,@10")
#pragma comment(linker, "/EXPORT:VerFindFileW=_FakeVerFindFileW,@11")
#pragma comment(linker, "/EXPORT:VerInstallFileA=_FakeVerInstallFileA,@12")
#pragma comment(linker, "/EXPORT:VerInstallFileW=_FakeVerInstallFileW,@13")
#pragma comment(linker, "/EXPORT:VerLanguageNameA=_FakeVerLanguageNameA,@14")
#pragma comment(linker, "/EXPORT:VerLanguageNameW=_FakeVerLanguageNameW,@15")
#pragma comment(linker, "/EXPORT:VerQueryValueA=_FakeVerQueryValueA,@16")
#pragma comment(linker, "/EXPORT:VerQueryValueW=_FakeVerQueryValueW,@17")
