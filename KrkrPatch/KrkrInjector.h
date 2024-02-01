#pragma once

class KrkrInjector
{
public:
    static void             Init            (const std::function<BOOL(HMODULE)>& beforeInjectCallback, const std::function<void()>& handleInjectCallback);

private:
    static void             LoadLibCallback (HMODULE hModule);

    static HRESULT WINAPI   InjectV2Link    (iTVPFunctionExporter* pExporter);

    static inline decltype(InjectV2Link)*       OriginalV2Link;

    static inline std::function<BOOL(HMODULE)>  BeforeInjectCallback;
    static inline std::function<void()>         HandleInjectCallback;
};
