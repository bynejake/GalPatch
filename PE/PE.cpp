#include "PE.h"

using namespace std;

PVOID PE::FindData(LPCSTR lpPattern, size_t patternLen, BOOL onlyOnce)
{
	return FindData(GetModuleHandle(nullptr), lpPattern, patternLen, onlyOnce);
}

PVOID PE::FindData(HMODULE hModule, LPCSTR lpPattern, size_t patternLen, BOOL onlyOnce)
{
	for (const auto sections = GetSections(hModule); const auto& section : sections)
	{
		if (const auto found = FindData(section, lpPattern, patternLen))
			return found;

		if (onlyOnce)
			break;
	}
	return nullptr;
}

vector<PE::Section> PE::GetSections(HMODULE hModule)
{
	const auto pDosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(hModule);
	const auto pNtHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<DWORD>(hModule) + pDosHeader->e_lfanew);
	const auto pSectionHeaders = IMAGE_FIRST_SECTION(pNtHeaders);

	vector<Section> sections;
	for (int i = 0; i < pNtHeaders->FileHeader.NumberOfSections; i++)
	{
		Section section
		{
			.Address			= reinterpret_cast<DWORD>(hModule) + pSectionHeaders[i].VirtualAddress,
			.Size				= pSectionHeaders[i].SizeOfRawData,
			.Characteristics	= pSectionHeaders[i].Characteristics
		};
		memcpy(section.Name, pSectionHeaders[i].Name, IMAGE_SIZEOF_SHORT_NAME);
		sections.emplace_back(section);
	}
	return sections;
}

PVOID PE::FindData(const Section& section, LPCSTR pPattern, size_t patternLen)
{
	auto addr = section.Address;
	for (const auto end = addr + section.Size - patternLen; addr <= end; addr++)
	{
		bool failed = false;
		for (size_t offset = 0; offset < patternLen; offset++)
		{
			if (const auto code = *reinterpret_cast<PCHAR>(addr + offset); pPattern[offset] != 0x2A && pPattern[offset] != code)
			{
				failed = true;
				break;
			}
		}
		if (failed)
			continue;

		return reinterpret_cast<PVOID>(addr);
	}
	return nullptr;
}
