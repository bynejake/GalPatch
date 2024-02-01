#include "pch.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        Hijacker::Hijack(L"Krkr");
        LoadLibHooker::Hook();
        CompilerHelper::Init();

#ifdef _DEBUG
        KrkrLogger::Start();

        spdlog::info("CompilerType {}", CompilerHelper::CompilerType == CompilerType::Borland ? "Borland" : "Msvc");
#endif

        KrkrInjector::Init(
            [](HMODULE hModule)
            {
                return KrkrPatcher::PatchSignVerify(hModule);
            },
            []
            {
                KrkrPatcher::PatchCreateStream();
            });
        break;
    case DLL_PROCESS_DETACH:
#ifdef _DEBUG
        KrkrLogger::Stop();
#endif

        LoadLibHooker::Unhook();
        Hijacker::Release();
        break;
    default:
        break;
    }

    return TRUE;
}
