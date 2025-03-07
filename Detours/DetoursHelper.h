#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <utility>
#include <detours/detours.h>

class DetoursHelper final
{
public:
    template <typename... T>
    static void             Hook            (const std::pair<T**, T*>... pairFucs)
    {
        InvokeDetourFunc(DetourAttach, pairFucs...);
    }

    template <typename... T>
    static void             Unhook          (const std::pair<T**, T*>... pairFucs)
    {
        InvokeDetourFunc(DetourDetach, pairFucs...);
    }

    static BOOL             FindExport      (HMODULE hModule, LPCSTR pszName);
    static PVOID            FindExportEx    (HMODULE hModule, LPCSTR pszName);
    static BOOL             FindImport      (HMODULE hModule, LPCSTR pszName);
    static PVOID*           FindImportEx    (HMODULE hModule, LPCSTR pszName);

private:
    template <typename F, typename... T>
    static void             InvokeDetourFunc(F pDetourFunc, const std::pair<T**, T*>... pairFucs)
    {
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        (..., pDetourFunc(reinterpret_cast<PVOID*>(pairFucs.first), reinterpret_cast<PVOID>(pairFucs.second)));
        DetourTransactionCommit();
    }

    struct FindExportContext
    {
        LPCSTR  pszName;
        PVOID   pvFunc;
    };

    struct FindImportContext
    {
        LPCSTR  pszName;
        PVOID*  ppvFunc;
    };

    static BOOL CALLBACK    CheckExport     (PVOID pContext, DWORD, LPCSTR pszName, PVOID   pvFunc);
    static BOOL CALLBACK    CheckImport     (PVOID pContext, DWORD, LPCSTR pszName, PVOID*  ppvFunc);
};
