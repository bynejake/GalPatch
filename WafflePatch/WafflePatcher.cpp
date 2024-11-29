#include "pch.h"

// Now only applicable to game : ¥Ê¥¤¥·¥ç¤ÎŠ¦Òù¡«ÕæÏÄ¤Îº¹¤À¤¯½»Î²¡«
//void WafflePatcher::PatchProtectedExeEncode()
//{
//    struct MemoryPatch
//    {
//        DWORD               rva;
//        DWORD               check;
//        std::vector<BYTE>   val;
//    };
//
//    static std::vector<MemoryPatch> patches =
//    {
//        // encoding
//        {0x000D6D24, 0x00008068, {0x68, 0x86}},
//        // boundary
//        {0x0005BB6A, 0x06769F3C, {0x3C, 0xFE}},
//        // font
//        {
//            0x0027EE34, 0X72826c82,
//            {0x55, 0x6E, 0x69, 0x66, 0x6F, 0x6E, 0x74, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
//        }
//    };
//
//    static const auto ImageBase = Pe::GetOptionalHeader()->ImageBase;
//    std::erase_if(patches, [](const MemoryPatch& patch)
//    {
//        if (const auto addr = reinterpret_cast<DWORD*>(ImageBase + patch.rva); *addr == patch.check)
//        {
//            std::memcpy(addr, patch.val.data(), patch.val.size());
//            return true;
//        }
//        return false;
//    });
//}

void WafflePatcher::PatchGetTextCrash()
{
    if (OriginalGetTextExtentPoint32A != nullptr)
        return;

    OriginalGetTextExtentPoint32A = GetTextExtentPoint32A;
    DetoursHelper::Hook(std::pair(&OriginalGetTextExtentPoint32A, PatchGetTextExtentPoint32A));
}

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
