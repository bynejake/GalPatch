#include "pch.h"

using namespace std;

void KrkrHooker::Hook(const std::function<BOOL(HMODULE)>& beforeV2LinkCallback, const std::function<void()>& afterV2LinkCallback)
{
    LoadLibHooker::Hook(LoadLibCallback);
    BeforeV2LinkCallback    = beforeV2LinkCallback;
    AfterV2LinkCallback     = afterV2LinkCallback;
}

void KrkrHooker::Unhook()
{
    // TODO what?
}

void KrkrHooker::LoadLibCallback(HMODULE hModule)
{
    if (BeforeV2LinkCallback == nullptr && AfterV2LinkCallback == nullptr)
        return;

    if (const auto pV2Link = DetoursHelper::FindExportEx(hModule, "V2Link"); pV2Link != nullptr)
    {
        if (DetoursHelper::FindImport(hModule, "ImageUnload"))
        {
            spdlog::info("Found ImageUnload, postpone HookV2Link");
            OriginalImageUnload = ImageUnload;
            DetoursHelper::Hook(pair(&OriginalImageUnload, HookImageUnload));
            return;
        }

        if (BeforeV2LinkCallback != nullptr && BeforeV2LinkCallback(hModule))
        {
            BeforeV2LinkCallback = nullptr;
        }

        if (AfterV2LinkCallback != nullptr)
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

    AfterV2LinkCallback();
    AfterV2LinkCallback = nullptr;

    const auto result = OriginalV2Link(pExporter);
    OriginalV2Link = nullptr;
    return result;
}

BOOL KrkrHooker::HookImageUnload(PLOADED_IMAGE ploadedImage)
{
    spdlog::info("HookImageUnload {}", ploadedImage->ModuleName);
    DetoursHelper::Unhook(pair(&OriginalImageUnload, HookImageUnload));
    OriginalImageUnload = nullptr;
    return ImageUnload(ploadedImage);
}
