#include "pch.h"

//#include <fstream>
//
//#include "nlohmann/json.hpp"
//
//void WafflePatcher::PatchProtectedExeEncode()
//{
//    struct MemoryPatch
//    {
//        std::string         type;
//        DWORD               rva;
//        DWORD               check;
//        std::vector<BYTE>   val;
//    };
//
//    static std::vector<MemoryPatch> sPatches = []
//    {
//        std::vector<MemoryPatch> patches;
//        if (std::ifstream jFile(PathUtil::GetAppPath() + L"version.json"); jFile.is_open())
//        {
//#define Str2Hex(str) (std::stoul(str, nullptr, 16))
//            for (const auto jConfig = nlohmann::json::parse(jFile); const auto& jPatch : jConfig["MemoryPatch"])
//            {
//                MemoryPatch patch
//                {
//                    .type   =           jPatch["type"]. get<std::string>(),
//                    .rva    = Str2Hex(  jPatch["rva"].  get<std::string>()),
//                    .check  = Str2Hex(  jPatch["check"].get<std::string>())
//                };
//
//                for (const auto& jValElem : jPatch["val"])
//                {
//                    patch.val.emplace_back(static_cast<BYTE>(Str2Hex(jValElem.get<std::string>())));
//                }
//
//                patches.emplace_back(patch);
//            }
//#undef Str2Hex
//        }
//        return patches;
//    }();
//
//    static const auto ImageBase = Pe::GetOptionalHeader()->ImageBase;
//    std::erase_if(sPatches, [](const MemoryPatch& patch)
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
