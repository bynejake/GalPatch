#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

class Core
{
protected:
    static void Hijack  (LPCTSTR lpDllName, LPCTSTR lpSrc);
    static void Release ();

    static inline HMODULE RealDll;

#define RESOLVE(fn) Original##fn = GetProcAddress(RealDll, #fn)
};
