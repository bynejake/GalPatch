#include "pch.h"

void KrkrInjector::Inject(const std::function<BOOL(HMODULE)>& foundV2Callback, const std::function<void()>& handleV2Callback)
{
    LoadLibHooker::Hook(LoadLibCallback);

    FoundV2Callback     = foundV2Callback;
    HandleV2Callback    = handleV2Callback;
}

void KrkrInjector::Eject()
{
    FoundV2Callback     = nullptr;
    HandleV2Callback    = nullptr;

    LoadLibHooker::Unhook(LoadLibCallback);
}

void KrkrInjector::LoadLibCallback(HMODULE hModule)
{
    if (FoundV2Callback == nullptr && HandleV2Callback == nullptr)
        return;

    if (const auto pV2Link = DetoursHelper::FindExportEx(hModule, "V2Link"); pV2Link != nullptr)
    {
        // find ImageUnload before find V2Link?
        if (DetoursHelper::FindImport(hModule, "ImageUnload"))
        {
            LOG(L"KrkrPatch: Found ImageUnload, postpone Inject!");
            return;
        }

        if (FoundV2Callback != nullptr && FoundV2Callback(hModule))
            FoundV2Callback = nullptr;

        if (HandleV2Callback != nullptr)
        {
            OriginalV2Link = reinterpret_cast<decltype(InjectV2Link)*>(pV2Link);
            DetoursHelper::Hook(std::pair(&OriginalV2Link, InjectV2Link));
        }
    }
}

HRESULT KrkrInjector::InjectV2Link(iTVPFunctionExporter* pExporter)
{
    LOG(L"KrkrPatch: InjectV2Link!");

    DetoursHelper::Unhook(std::pair(&OriginalV2Link, InjectV2Link));

    TVPInitImportStub(pExporter);

    HandleV2Callback();
    HandleV2Callback = nullptr;

    return OriginalV2Link(pExporter);
}
