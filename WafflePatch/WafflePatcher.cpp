#include "pch.h"

//#include <fstream>
//
//#include "nlohmann/json.hpp"
//
//struct MemoryPatch
//{
//    std::string         cmt;
//    DWORD               rva;
//    DWORD               chk;
//    std::vector<BYTE>   val;
//
//    static DWORD Str2Hex(const std::string& str)
//    {
//        return std::stoul(str, nullptr, 16);
//    }
//
//    friend void from_json(const nlohmann::json& jPatch, MemoryPatch& patch)
//    {
//        patch.cmt =         jPatch["cmt"];
//        patch.rva = Str2Hex(jPatch["rva"]);
//        patch.chk = Str2Hex(jPatch["chk"]);
//
//        for (const auto& jValElem : jPatch["val"])
//        {
//            patch.val.emplace_back(static_cast<BYTE>(Str2Hex(jValElem)));
//        }
//    }
//};
//
//void WafflePatcher::PatchProtectedExeEncode()
//{
//    static std::vector<MemoryPatch> sPatches = []
//    {
//        std::vector<MemoryPatch> patches;
//        if (std::ifstream jFile(PathUtil::GetAppPath() + L"version.json"); jFile.is_open())
//        {
//            const auto jConfig = nlohmann::json::parse(jFile);
//            patches = jConfig["MemoryPatch"];
//        }
//        return patches;
//    }();
//
//    static const auto ImageBase = Pe::GetOptionalHeader()->ImageBase;
//    std::erase_if(sPatches, [](const MemoryPatch& patch)
//    {
//        if (const auto addr = reinterpret_cast<DWORD*>(ImageBase + patch.rva); *addr == patch.chk)
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
