#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include "PathUtil.h"

using namespace std;

std::string PathUtil::GetAppPathA()
{
    CHAR filePath[MAX_PATH];
    GetModuleFileNameA(GetModuleHandleA(nullptr), filePath, MAX_PATH);

    const auto aFilePathStr = string(filePath);

    auto pos = aFilePathStr.find_last_of('\\');
    if (pos != string::npos)
        pos += 1;

    return aFilePathStr.substr(0, pos);
}

std::wstring PathUtil::GetAppPathW()
{
    WCHAR filePath[MAX_PATH];
    GetModuleFileNameW(GetModuleHandleW(nullptr), filePath, MAX_PATH);

    const auto wFilePathStr = wstring(filePath);

    auto pos = wFilePathStr.find_last_of(L'\\');
    if (pos != wstring::npos)
        pos += 1;

    return wFilePathStr.substr(0, pos);
}
