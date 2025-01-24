#include "pch.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        Hijacker::Hijack(L"Krkr");
        LoadLibHooker::Hook();
        CompilerHelper::Analyze();

        LOG(L"KrkrPatch: CompilerType {}.", CompilerHelper::CompilerType == CompilerType::Borland ? L"Borland" : L"Msvc");

        KrkrInjector::Inject(
            [](HMODULE lhModule)
            {
                return KrkrPatcher::PatchSignVerify(lhModule);
            },
            []
            {
                KrkrPatcher::PatchCreateStream();
            });
        break;
    case DLL_PROCESS_DETACH:
        KrkrPatcher::Unpatch();
        KrkrInjector::Eject();
        LoadLibHooker::Unhook();
        Hijacker::Release();
        break;
    default:
        break;
    }

    return TRUE;
}
