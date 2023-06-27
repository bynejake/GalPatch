#include "pch.h"

using namespace std;

void KrkrHooker::Hook(const std::function<BOOL(HMODULE)>& beforeV2LinkCallback, const std::function<void()>& handleV2LinkCallback)
{
    LoadLibHooker::Hook(LoadLibCallback);
    BeforeV2LinkCallback = beforeV2LinkCallback;
    HandleV2LinkCallback = handleV2LinkCallback;
}

void KrkrHooker::Unhook()
{
}

void KrkrHooker::LoadLibCallback(HMODULE hModule)
{
    if (BeforeV2LinkCallback == nullptr && HandleV2LinkCallback == nullptr)
        return;

    if (const auto pV2Link = DetoursHelper::FindExportEx(hModule, "V2Link"); pV2Link != nullptr)
    {
        // find ImageUnload before find V2Link?
        if (DetoursHelper::FindImport(hModule, "ImageUnload"))
            return spdlog::info("Found ImageUnload, postpone Bypass & V2Link");

        if (BeforeV2LinkCallback != nullptr && BeforeV2LinkCallback(hModule))
            BeforeV2LinkCallback = nullptr;

        if (HandleV2LinkCallback != nullptr)
        {
            OriginalV2Link = reinterpret_cast<decltype(HookV2Link)*>(pV2Link);
            DetoursHelper::Hook(pair(&OriginalV2Link, HookV2Link));
        }
    }
}

HRESULT KrkrHooker::HookV2Link(iTVPFunctionExporter* pExporter)
{
    spdlog::info("HookV2Link");

    DetoursHelper::Unhook(pair(&OriginalV2Link, HookV2Link));

    TVPInitImportStub(pExporter);

    HandleV2LinkCallback();
    HandleV2LinkCallback = nullptr;

    return OriginalV2Link(pExporter);
}
