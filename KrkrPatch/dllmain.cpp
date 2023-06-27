#include "pch.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        Hijacker::Hijack(L"Krkr");
        LoadLibHooker::Hook();
        CompilerHelper::Init();
        KrkrLogger::Start();

        spdlog::info("CompilerType {}", CompilerHelper::CompilerType == CompilerType::Borland ? "Borland" : "Msvc");

        KrkrHooker::Hook(
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
        KrkrPatcher::Unpatch();
        KrkrHooker::Unhook();
        KrkrLogger::Stop();
        LoadLibHooker::Unhook();
        Hijacker::Release();
        break;
    default:
        break;
    }

    return TRUE;
}
