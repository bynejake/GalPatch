#include "pch.h"

using namespace std;

void KrkrInjector::Init(const std::function<BOOL(HMODULE)>& beforeInjectCallback, const std::function<void()>& handleInjectCallback)
{
    LoadLibHooker::Hook(LoadLibCallback);
    BeforeInjectCallback = beforeInjectCallback;
    HandleInjectCallback = handleInjectCallback;
}

void KrkrInjector::LoadLibCallback(HMODULE hModule)
{
    if (BeforeInjectCallback == nullptr && HandleInjectCallback == nullptr)
        return;

    if (const auto pV2Link = DetoursHelper::FindExportEx(hModule, "V2Link"); pV2Link != nullptr)
    {
        // find ImageUnload before find V2Link?
        if (DetoursHelper::FindImport(hModule, "ImageUnload"))
            return spdlog::info("Found ImageUnload, postpone Inject");

        if (BeforeInjectCallback != nullptr && BeforeInjectCallback(hModule))
            BeforeInjectCallback = nullptr;

        if (HandleInjectCallback != nullptr)
        {
            OriginalV2Link = reinterpret_cast<decltype(InjectV2Link)*>(pV2Link);
            DetoursHelper::Hook(pair(&OriginalV2Link, InjectV2Link));
        }
    }
}

HRESULT KrkrInjector::InjectV2Link(iTVPFunctionExporter* pExporter)
{
    spdlog::info("InjectV2Link");

    DetoursHelper::Unhook(pair(&OriginalV2Link, InjectV2Link));

    TVPInitImportStub(pExporter);

    HandleInjectCallback();
    HandleInjectCallback = nullptr;

    return OriginalV2Link(pExporter);
}
