#include "Core.h"

#include <tchar.h>

void Core::Hijack(LPCTSTR lpDllName, LPCTSTR lpSrc)
{
    if (RealDll != nullptr)
        return;

    TCHAR realDllPath[MAX_PATH];
    GetSystemDirectory(realDllPath, MAX_PATH);
    _tcscat_s(realDllPath, _T("\\"));
    _tcscat_s(realDllPath, lpDllName);

    RealDll = LoadLibrary(realDllPath);
    if (RealDll == nullptr)
    {
        TCHAR errorMessage[256] = _T("");
        _stprintf_s(errorMessage, _T("Cannot load Original %s library!"), lpDllName);

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
