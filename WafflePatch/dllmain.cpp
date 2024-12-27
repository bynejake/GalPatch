#include "pch.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        Hijacker::Hijack(L"Waffle");
        LoadLibHooker::Hook();
        WaffleInjector::Inject(
            []
            {
                WafflePatcher::PatchProtectedExeEncoding();
                WafflePatcher::PatchGetTextCrash();
            });
        break;
    case DLL_PROCESS_DETACH:
        WafflePatcher::Unpatch();
        WaffleInjector::Eject();
        LoadLibHooker::Unhook();
        Hijacker::Release();
        break;
    default:
        break;
    }

    return TRUE;
}
