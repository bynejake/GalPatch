#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include "PathUtil.h"

using namespace std;

wstring PathUtil::GetAppPath()
{
    WCHAR filePath[MAX_PATH];
    GetModuleFileName(GetModuleHandle(nullptr), filePath, MAX_PATH);

    const auto wFilePath = std::wstring(filePath);

    auto pos = wFilePath.find_last_of(L'\\');
    if (pos != wstring::npos)
        pos += 1;

    return wFilePath.substr(0, pos);
}
