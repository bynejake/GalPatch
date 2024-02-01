#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <string>

class FileStream
{
public:
    FileStream(const std::string&   path, const char*    mode);
    FileStream(const std::wstring&  path, const wchar_t* mode);

    ~FileStream();

    void    Seek        (INT64 offset) const;
    void    SetPos      (INT64 pos) const;
    INT64   GetPos      () const;
    void    ReadBytes   (PVOID pBuffer, size_t size) const;
    void    WriteBytes  (PVOID pBuffer, size_t size) const;

private:
    FILE* pFile{};
};
