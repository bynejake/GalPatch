#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <vector>

class Pe final
{
public:
    static PIMAGE_DOS_HEADER        GetDosHeader        ();
    static PIMAGE_NT_HEADERS        GetNtHeaders        ();
    static PIMAGE_OPTIONAL_HEADER   GetOptionalHeader   ();

    static PVOID                    FindData            (                           LPCSTR lpPattern, size_t patternLen, BOOL onlyOnce = FALSE);
    static PVOID                    FindData            (HMODULE hModule,           LPCSTR lpPattern, size_t patternLen, BOOL onlyOnce = FALSE);

private:
    struct Section
    {
        BYTE    name[IMAGE_SIZEOF_SHORT_NAME];
        DWORD   address;
        DWORD   size;
        DWORD   characteristics;
    };

    static std::vector<Section>     GetSections         (HMODULE hModule);
    static PVOID                    FindData            (const Section& section,    LPCSTR lpPattern, size_t patternLen);
};
