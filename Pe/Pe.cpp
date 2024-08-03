#include "Pe.h"

PVOID Pe::FindData(LPCSTR lpPattern, size_t patternLen, BOOL onlyOnce)
{
    return FindData(GetModuleHandle(nullptr), lpPattern, patternLen, onlyOnce);
}

PVOID Pe::FindData(HMODULE hModule, LPCSTR lpPattern, size_t patternLen, BOOL onlyOnce)
{
    for (const auto sections = GetSections(hModule); const auto& section : sections)
    {
        if (const auto found = FindData(section, lpPattern, patternLen); found != nullptr)
            return found;

        if (onlyOnce)
            break;
    }
    return nullptr;
}

std::vector<Pe::Section> Pe::GetSections(HMODULE hModule)
{
    const auto pDosHeader       = reinterpret_cast<PIMAGE_DOS_HEADER>(hModule);
    const auto pNtHeaders       = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<DWORD>(hModule) + pDosHeader->e_lfanew);
    const auto pSectionHeaders  = IMAGE_FIRST_SECTION(pNtHeaders);

    std::vector<Section> sections;
    for (int i = 0; i < pNtHeaders->FileHeader.NumberOfSections; i++)
    {
        Section section
        {
            .address            = reinterpret_cast<DWORD>(hModule) + pSectionHeaders[i].VirtualAddress,
            .size               = pSectionHeaders[i].SizeOfRawData,
            .characteristics    = pSectionHeaders[i].Characteristics
        };
        memcpy(section.name, pSectionHeaders[i].Name, IMAGE_SIZEOF_SHORT_NAME);
        sections.emplace_back(section);
    }
    return sections;
}

PVOID Pe::FindData(const Section& section, LPCSTR lpPattern, size_t patternLen)
{
    auto addr = section.address;
    for (const auto end = addr + section.size - patternLen; addr <= end; addr++)
    {
        BOOL failed = FALSE;
        for (size_t offset = 0; offset < patternLen; offset++)
        {
            if (const auto code = *reinterpret_cast<PCHAR>(addr + offset); lpPattern[offset] != 0x2A && lpPattern[offset] != code)
            {
                failed = TRUE;
                break;
            }
        }
        if (failed)
            continue;

        return reinterpret_cast<PVOID>(addr);
    }
    return nullptr;
}
