#pragma once

class KrkrInjector
{
public:
    static void             Inject          (const std::function<BOOL(HMODULE)>& foundV2Callback, const std::function<void()>& injectV2Callback);
    static void             Eject           ();

private:
    static void             LoadLibCallback (HMODULE hModule);

    static HRESULT WINAPI   InjectV2Link    (iTVPFunctionExporter* pExporter);

    static inline decltype(InjectV2Link)*       OriginalV2Link;

    static inline std::function<BOOL(HMODULE)>  FoundV2Callback;
    static inline std::function<void()>         InjectV2Callback;
};
