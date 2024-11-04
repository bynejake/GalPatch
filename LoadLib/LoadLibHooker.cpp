#include "LoadLibHooker.h"
#include "DetoursHelper.h"

void LoadLibHooker::Hook(const std::function<void(HMODULE)>& callback)
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
        std::pair(&OriginalLoadLibraryA,     HookLoadLibraryA),
        std::pair(&OriginalLoadLibraryW,     HookLoadLibraryW),
        std::pair(&OriginalLoadLibraryExA,   HookLoadLibraryExA),
        std::pair(&OriginalLoadLibraryExW,   HookLoadLibraryExW)
    );
}

void LoadLibHooker::Unhook(const std::function<void(HMODULE)>& callback)
{
    if (OriginalLoadLibraryA == nullptr)
        return;

    if (callback != nullptr)
        std::erase_if(Callbacks, [callback](const std::function<void(HMODULE)>& it)
        {
            return *it.target<void(*)(HMODULE)>() == *callback.target<void(*)(HMODULE)>();
        });
    else
        Callbacks.clear();

    if (!Callbacks.empty())
        return;

    DetoursHelper::Unhook
    (
        std::pair(&OriginalLoadLibraryA,     HookLoadLibraryA),
        std::pair(&OriginalLoadLibraryW,     HookLoadLibraryW),
        std::pair(&OriginalLoadLibraryExA,   HookLoadLibraryExA),
        std::pair(&OriginalLoadLibraryExW,   HookLoadLibraryExW)
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
