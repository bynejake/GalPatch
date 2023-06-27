#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <vector>

class PE final
{
public:
    static PVOID                FindData    (                           LPCSTR lpPattern, size_t patternLen, BOOL onlyOnce = FALSE);
    static PVOID                FindData    (HMODULE hModule,           LPCSTR lpPattern, size_t patternLen, BOOL onlyOnce = FALSE);

private:
    struct Section
    {
        BYTE    Name[IMAGE_SIZEOF_SHORT_NAME];
        DWORD   Address;
        DWORD   Size;
        DWORD   Characteristics;
    };

    static std::vector<Section> GetSections (HMODULE hModule);
    static PVOID                FindData    (const Section& section,    LPCSTR lpPattern, size_t patternLen);
};
