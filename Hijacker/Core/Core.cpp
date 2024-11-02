#include "Core.h"

#include <wchar.h>

void Core::Hijack(LPCWSTR lpDllName, LPCWSTR lpSrc)
{
    if (RealDll != nullptr)
        return;

    WCHAR realDllPath[MAX_PATH];
    GetSystemDirectory(realDllPath, MAX_PATH);
    wcscat_s(realDllPath, L"\\");
    wcscat_s(realDllPath, lpDllName);

    RealDll = LoadLibrary(realDllPath);
    if (RealDll == nullptr)
    {
        WCHAR errorMessage[256] = L"";
        swprintf_s(errorMessage, L"Cannot load Original %s library!", lpDllName);

        MessageBox(nullptr, errorMessage, lpSrc, MB_ICONERROR);
        ExitProcess(0);
    }
}

void Core::Release()
{
    if (RealDll == nullptr)
        return;

    FreeLibrary(RealDll);
    RealDll = nullptr;
}
