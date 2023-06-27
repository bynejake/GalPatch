#pragma once

class KrkrHooker
{
public:
    static void             Hook            (const std::function<BOOL(HMODULE)>& beforeV2LinkCallback, const std::function<void()>& handleV2LinkCallback);
    static void             Unhook          ();

private:
    static void             LoadLibCallback (HMODULE hModule);

    static HRESULT WINAPI   HookV2Link      (iTVPFunctionExporter* pExporter);

    static inline decltype(HookV2Link)*         OriginalV2Link;

    static inline std::function<BOOL(HMODULE)>  BeforeV2LinkCallback;
    static inline std::function<void()>         HandleV2LinkCallback;
};
