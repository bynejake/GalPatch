#pragma once

#include <string>

class PathUtil final
{
public:
    static std::string  GetAppPathA();
    static std::wstring GetAppPathW();

#ifdef UNICODE
#define GetAppPath GetAppPathW
#else
#define GetAppPath GetAppPathA
#endif
};
