#include "pch.h"

#ifdef PROTECTED_EXE
struct MemoryPatch
{
    DWORD               rva;
    DWORD               chk;
    std::vector<BYTE>   val;
};

void WafflePatcher::PatchProtectedExeEncoding()
{
    static std::vector<MemoryPatch> sPatches =
    {
#ifdef KANIN
        // encoding
        {0x000D6D24, 0x00008068, {0x68, 0x86}},
        // boundary
        {0x0005BB6A, 0x06769F3C, {0x3C, 0xFE}},
        // font
        {0x0027EE34, 0x72826C82, {0x4C, 0x58, 0x47, 0x57, 0x20, 0x57, 0x4B, 0x20, 0x4C, 0x69, 0x74, 0x65, 0x00}}
#endif
    };

    static const auto ImageBase = Pe::GetOptionalHeader()->ImageBase;
    std::erase_if(sPatches, [](const MemoryPatch& patch)
    {
        if (const auto addr = reinterpret_cast<DWORD*>(ImageBase + patch.rva); *addr == patch.chk)
        {
            MemoryUtil::Write(addr, patch.val);
            return true;
        }
        return false;
    });
}
#endif

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
