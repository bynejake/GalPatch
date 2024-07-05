#include "pch.h"

void WaffleInjector::Inject(const std::function<void()>& callback)
{
    LoadLibHooker::Hook(LoadLibCallback);
    Callback = callback;
}

void WaffleInjector::Eject()
{
    Callback = nullptr;
    LoadLibHooker::Unhook(LoadLibCallback);
}

void WaffleInjector::LoadLibCallback(HMODULE hModule)
{
    if (Callback != nullptr)
        Callback();
}
