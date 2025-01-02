#pragma once

class KrkrPatcher
{
public:
    static BOOL                                                             PatchSignVerify         (HMODULE hModule);
    static void                                                             PatchCreateStream       ();
    static void                                                             Unpatch                 ();

private:
    static BOOL                 __fastcall                                  PatchSignVerifyMsvc     (HMODULE hModule);
    static tTJSBinaryStream*                                                PatchCreateStreamBorland(const ttstr& name, tjs_uint32 flags);
    static tTJSBinaryStream*    __fastcall                                  PatchCreateStreamMsvc   (const ttstr& name, tjs_uint32 flags);

    template <typename TArcStream, auto** TOriginalCreateStream>
    static tTJSBinaryStream*                                                PatchCreateStream       (const ttstr& name, tjs_uint32 flags);

    static std::pair<std::wstring, std::wstring>                            PatchUrl                (const ttstr& name, tjs_uint32 flags);
    static std::wstring                                                     PatchName               (const ttstr& name);

    static std::tuple<std::vector<std::wstring>, std::vector<std::wstring>> ListPatches             ();

    // temp for test
    //static void decrypt(tTJSBinaryStream* stream, std::vector<BYTE>& output);

    static inline decltype(PatchSignVerifyMsvc)*        OriginalSignVerifyMsvc;
    static inline decltype(PatchCreateStreamBorland)*   OriginalCreateStreamBorland;
    static inline decltype(PatchCreateStreamMsvc)*      OriginalCreateStreamMsvc;
};
