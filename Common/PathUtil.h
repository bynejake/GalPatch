#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <string>
#include <tchar.h>

class PathUtil final
{
public:
    template <typename T>
    static std::enable_if_t<std::is_same_v<T, std::wstring> || std::is_same_v<T, std::string>, T> GetAppPathTpl()
    {
        TCHAR pathBuffer[MAX_PATH];
        GetModuleFileName(nullptr, pathBuffer, MAX_PATH);
        T pathStr(pathBuffer);

        return pathStr.substr(0, pathStr.find_last_of(_T('\\')) + 1);
    }

#ifdef UNICODE
#define GetAppPath GetAppPathTpl<std::wstring>
#else
#define GetAppPath GetAppPathTpl<std::string>
#endif
};
