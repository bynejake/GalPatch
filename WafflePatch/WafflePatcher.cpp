#include "pch.h"

void WafflePatcher::Patch()
{
    //PatchProtectedExeEncode();

    if (OriginalGetTextExtentPoint32A != nullptr)
        return;

    OriginalGetTextExtentPoint32A = GetTextExtentPoint32A;
    DetoursHelper::Hook(std::pair(&OriginalGetTextExtentPoint32A, PatchGetTextExtentPoint32A));
}

// Now only applicable to game : ナイショの姦淫～真夏の汗だく交尾～ 
//void WafflePatcher::PatchProtectedExeEncode()
//{
//    struct MemoryPatch
//    {
//        DWORD* addr;
//        DWORD               check;
//        std::vector<BYTE>   patch;
//    };
//
//    static const MemoryPatch MemoryPatches[] = {
//        // encoding
//        {reinterpret_cast<DWORD*>(0x004D6D24), 0x00008068, {0x68, 0x86}},
//        // boundary
//        {reinterpret_cast<DWORD*>(0x0045BB6A), 0x06769F3C, {0x3C, 0xFE}},
//        // font
//        {
//            reinterpret_cast<DWORD*>(0x0067EE34), 0X72826c82,
//            {0x55, 0x6E, 0x69, 0x66, 0x6F, 0x6E, 0x74, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
//        }
//    };
//
//    for (const auto& [addr, check, patch] : MemoryPatches)
//    {
//        if (*addr == check)
//            std::memcpy(addr, patch.data(), patch.size());
//    }
//}

void WafflePatcher::Unpatch()
{
    if (OriginalGetTextExtentPoint32A == nullptr)
        return;

    DetoursHelper::Unhook(std::pair(&OriginalGetTextExtentPoint32A, PatchGetTextExtentPoint32A));
    OriginalGetTextExtentPoint32A = nullptr;
}

BOOL WafflePatcher::PatchGetTextExtentPoint32A(HDC hdc, LPCSTR lpString, int c, LPSIZE lpsz)
{
    if (strcmp(lpString, "\t") == 0)
    {
        LOG(L"WafflePatch: Found tab character!");
        lpString = " ";
    }

    return OriginalGetTextExtentPoint32A(hdc, lpString, c, lpsz);
}
