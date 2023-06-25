#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include "PathUtil.h"

std::wstring PathUtil::GetAppPath()
{
	WCHAR filePath[MAX_PATH];
	GetModuleFileName(GetModuleHandle(nullptr), filePath, MAX_PATH);

	const auto wFilePath = std::wstring(filePath);
	const auto pos = wFilePath.find_last_of(L'\\');
	return wFilePath.substr(0, min(pos + 1, std::string::npos));
}
