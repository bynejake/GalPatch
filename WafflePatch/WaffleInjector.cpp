#include "pch.h"

void WaffleInjector::Inject(const std::function<void()>& injectCallback)
{
    LoadLibHooker::Hook(LoadLibCallback);
    InjectCallback = injectCallback;
}

void WaffleInjector::Eject()
{
    InjectCallback = nullptr;
    //LoadLibHooker::Unhook();
}

void WaffleInjector::LoadLibCallback(HMODULE hModule)
{
    if (InjectCallback != nullptr)
        InjectCallback();
}
