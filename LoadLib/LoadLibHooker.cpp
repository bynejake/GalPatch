#include "LoadLibHooker.h"
#include "DetoursHelper.h"

using namespace std;

void LoadLibHooker::Hook(const function<void(HMODULE)>& callback)
{
	if (callback)
		Callbacks.emplace_back(callback);

	if (OriginalVirtualProtect)
		return;

	OriginalLoadLibraryA	= LoadLibraryA;
	OriginalLoadLibraryW	= LoadLibraryW;
	OriginalLoadLibraryExA	= LoadLibraryExA;
	OriginalLoadLibraryExW	= LoadLibraryExW;
	OriginalVirtualProtect	= VirtualProtect;

	DetoursHelper::Hook
	(
		pair(&OriginalLoadLibraryA,		HookLoadLibraryA),
		pair(&OriginalLoadLibraryW,		HookLoadLibraryW),
		pair(&OriginalLoadLibraryExA,	HookLoadLibraryExA),
		pair(&OriginalLoadLibraryExW,	HookLoadLibraryExW),
		pair(&OriginalVirtualProtect,	HookVirtualProtect)
	);
}

void LoadLibHooker::Unhook()
{
	if (!OriginalVirtualProtect)
		return;

	Callbacks.clear();

	DetoursHelper::Unhook
	(
		pair(&OriginalLoadLibraryA,		HookLoadLibraryA),
		pair(&OriginalLoadLibraryW,		HookLoadLibraryW),
		pair(&OriginalLoadLibraryExA,	HookLoadLibraryExA),
		pair(&OriginalLoadLibraryExW,	HookLoadLibraryExW),
		pair(&OriginalVirtualProtect,	HookVirtualProtect)
	);

	OriginalLoadLibraryA	= nullptr;
	OriginalLoadLibraryW	= nullptr;
	OriginalLoadLibraryExA	= nullptr;
	OriginalLoadLibraryExW	= nullptr;
	OriginalVirtualProtect	= nullptr;
}

HMODULE LoadLibHooker::HookLoadLibraryA(LPCSTR lpLibFileName)
{
	const auto hModule = OriginalLoadLibraryA(lpLibFileName);
	InvokeCallbacks(hModule);
	return hModule;
}

HMODULE LoadLibHooker::HookLoadLibraryW(LPCWSTR lpLibFileName)
{
	const auto hModule = OriginalLoadLibraryW(lpLibFileName);
	InvokeCallbacks(hModule);
	return hModule;
}

HMODULE LoadLibHooker::HookLoadLibraryExA(LPCSTR lpLibFileName, HANDLE hFile, DWORD dwFlags)
{
	const auto hModule = OriginalLoadLibraryExA(lpLibFileName, hFile, dwFlags);
	InvokeCallbacks(hModule);
	return hModule;
}

HMODULE LoadLibHooker::HookLoadLibraryExW(LPCWSTR lpLibFileName, HANDLE hFile, DWORD dwFlags)
{
	const auto hModule = OriginalLoadLibraryExW(lpLibFileName, hFile, dwFlags);
	InvokeCallbacks(hModule);
	return hModule;
}

BOOL LoadLibHooker::HookVirtualProtect(LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect, PDWORD lpflOldProtect)
{
	if (!OriginalVirtualProtect(lpAddress, dwSize, flNewProtect, lpflOldProtect))
		return FALSE;

	if (flNewProtect != PAGE_EXECUTE_READ)
		return TRUE;

	BYTE* hModule = static_cast<BYTE*>(lpAddress) - 0x1000;
	MEMORY_BASIC_INFORMATION memInfo;

	if (VirtualQuery(hModule, &memInfo, sizeof(memInfo)) == 0)
		return TRUE;

	if (memInfo.AllocationBase != hModule ||
		memInfo.RegionSize != 0x1000 ||
		memInfo.State != MEM_COMMIT ||
		memInfo.Type != MEM_PRIVATE ||
		hModule[0] != 'M' ||
		hModule[1] != 'Z')
	{
		return TRUE;
	}

	InvokeCallbacks(reinterpret_cast<HMODULE>(hModule));

	return TRUE;
}

void LoadLibHooker::InvokeCallbacks(HMODULE hModule)
{
	if (hModule != nullptr)
		for (const auto& callback : Callbacks)
		{
			callback(hModule);
		}
}
