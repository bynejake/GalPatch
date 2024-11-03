#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

class Core
{
protected:
    static void Hijack  (LPCTSTR lpDllName, LPCTSTR lpSrc);
    static void Release ();

    static inline HMODULE RealDll;

#define DECLARE_ORIGINAL_FUNC(fn) static inline PVOID Original##fn;
#define RESOLVE_ORIGINAL_FUNC(fn) Original##fn = GetProcAddress(RealDll, #fn);

#define DECLARE_FAKE_FUNC(fn, cls) EXTERN_C __declspec(naked) void Fake##fn() { __asm { jmp [##cls::Original##fn] } }
#define EXPORT_FAKE_FUNC(fn, idx) __pragma(comment(linker, "/EXPORT:" #fn "=_Fake" #fn ",@" #idx))
};
