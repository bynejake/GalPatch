#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <functional>

class LoadLibHooker final
{
public:
    static void                     Hook                (const std::function<void(HMODULE)>& callback = nullptr);
    static void                     Unhook              ();

private:
    static inline HMODULE   WINAPI  HookLoadLibraryA    (LPCSTR  lpLibFileName);
    static inline HMODULE   WINAPI  HookLoadLibraryW    (LPCWSTR lpLibFileName);
    static inline HMODULE   WINAPI  HookLoadLibraryExA  (LPCSTR  lpLibFileName, HANDLE hFile, DWORD dwFlags);
    static inline HMODULE   WINAPI  HookLoadLibraryExW  (LPCWSTR lpLibFileName, HANDLE hFile, DWORD dwFlags);

    static inline void              InvokeCallbacks     (HMODULE hModule);

    static inline decltype(LoadLibraryA)*                   OriginalLoadLibraryA;
    static inline decltype(LoadLibraryW)*                   OriginalLoadLibraryW;
    static inline decltype(LoadLibraryExA)*                 OriginalLoadLibraryExA;
    static inline decltype(LoadLibraryExW)*                 OriginalLoadLibraryExW;

    static inline std::vector<std::function<void(HMODULE)>> Callbacks;
};
