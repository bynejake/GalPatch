#include "FileStream.h"

FileStream::FileStream(const std::string& path, const char* mode)
{
    fopen_s(&pFile, path.c_str(), mode);
}

FileStream::FileStream(const std::wstring& path, const wchar_t* mode)
{
    _wfopen_s(&pFile, path.c_str(), mode);
}

FileStream::~FileStream()
{
    fclose(pFile);
}

void FileStream::Seek(INT64 offset) const
{
    _fseeki64(pFile, offset, SEEK_CUR);
}

void FileStream::SetPos(INT64 pos) const
{
    _fseeki64(pFile, pos, SEEK_SET);
}

INT64 FileStream::GetPos() const
{
    return _ftelli64(pFile);
}

void FileStream::ReadBytes(PVOID pBuffer, size_t size) const
{
    fread(pBuffer, 1, size, pFile);
}

void FileStream::WriteBytes(PVOID pBuffer, size_t size) const
{
    fwrite(pBuffer, 1, size, pFile);
}
