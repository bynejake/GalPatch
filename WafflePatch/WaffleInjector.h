#pragma once

class WaffleInjector
{
public:
    static void Inject          (const std::function<void()>& injectCallback);
    static void Eject           ();

private:
    static void LoadLibCallback (HMODULE hModule);

    static inline std::function<void()> InjectCallback;
};
