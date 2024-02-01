#include "LoadLibHooker.h"
#include "DetoursHelper.h"

using namespace std;

void LoadLibHooker::Hook(const function<void(HMODULE)>& callback)
{
    if (callback != nullptr)
        Callbacks.emplace_back(callback);

    if (OriginalLoadLibraryA != nullptr)
        return;

    OriginalLoadLibraryA    = LoadLibraryA;
    OriginalLoadLibraryW    = LoadLibraryW;
    OriginalLoadLibraryExA  = LoadLibraryExA;
    OriginalLoadLibraryExW  = LoadLibraryExW;

    DetoursHelper::Hook
    (
        pair(&OriginalLoadLibraryA,     HookLoadLibraryA),
        pair(&OriginalLoadLibraryW,     HookLoadLibraryW),
        pair(&OriginalLoadLibraryExA,   HookLoadLibraryExA),
        pair(&OriginalLoadLibraryExW,   HookLoadLibraryExW)
    );
}

void LoadLibHooker::Unhook()
{
    if (OriginalLoadLibraryA == nullptr)
        return;

    Callbacks.clear();

    DetoursHelper::Unhook
    (
        pair(&OriginalLoadLibraryA,     HookLoadLibraryA),
        pair(&OriginalLoadLibraryW,     HookLoadLibraryW),
        pair(&OriginalLoadLibraryExA,   HookLoadLibraryExA),
        pair(&OriginalLoadLibraryExW,   HookLoadLibraryExW)
    );

    OriginalLoadLibraryA    = nullptr;
    OriginalLoadLibraryW    = nullptr;
    OriginalLoadLibraryExA  = nullptr;
    OriginalLoadLibraryExW  = nullptr;
}

HMODULE LoadLibHooker::HookLoadLibraryA(LPCSTR lpLibFileName)
{
    const auto hModule = OriginalLoadLibraryA(lpLibFileName);
    InvokeCallbacks(hModule);
    return hModule;
}

HMODULE LoadLibHooker::HookLoadLibraryW(LPCWSTR lpLibFileName)
{
    const auto hModule = OriginalLoadLibraryW(lpLibFileName);
    InvokeCallbacks(hModule);
    return hModule;
}

HMODULE LoadLibHooker::HookLoadLibraryExA(LPCSTR lpLibFileName, HANDLE hFile, DWORD dwFlags)
{
    const auto hModule = OriginalLoadLibraryExA(lpLibFileName, hFile, dwFlags);
    InvokeCallbacks(hModule);
    return hModule;
}

HMODULE LoadLibHooker::HookLoadLibraryExW(LPCWSTR lpLibFileName, HANDLE hFile, DWORD dwFlags)
{
    const auto hModule = OriginalLoadLibraryExW(lpLibFileName, hFile, dwFlags);
    InvokeCallbacks(hModule);
    return hModule;
}

void LoadLibHooker::InvokeCallbacks(HMODULE hModule)
{
    if (hModule != nullptr)
        for (const auto& callback : Callbacks)
            callback(hModule);
}
