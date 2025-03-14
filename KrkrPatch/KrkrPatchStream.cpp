#include "pch.h"

#ifdef _MSC_VER
#pragma warning(disable : 4244)
#endif

tjs_uint64 KrkrPatchStream::Seek(tjs_int64 offset, tjs_int whence)
{
    switch (whence)
    {
    case SEEK_SET:
        pos = offset;
        break;
    case SEEK_CUR:
        pos += offset;
        break;
    case SEEK_END:
        pos = data.size() + offset;
        break;
    default:
        break;
    }
    return pos;
}

tjs_uint KrkrPatchStream::Read(void* buffer, tjs_uint read_size)
{
    read_size = min(read_size, data.size() - pos);

    memcpy(buffer, data.data() + pos, read_size);
    pos += read_size;

    return read_size;
}

tjs_uint KrkrPatchStream::Write(const void*, tjs_uint)
{
    throw std::exception("Not implemented!");
}

void KrkrPatchStream::SetEndOfStorage()
{
    throw std::exception("Not implemented!");
}

tjs_uint64 KrkrPatchStream::GetSize()
{
    return data.size();
}

KrkrPatchSigStream::KrkrPatchSigStream()
{
    static constexpr auto SIG_SKIP = "skip!";
    data = std::vector<BYTE>(SIG_SKIP, SIG_SKIP + strlen(SIG_SKIP));
}

KrkrPatchArcStream::KrkrPatchArcStream(const std::wstring& patchArc, const XP3ArchiveSegment* segment)
{
    data.resize(segment->OrgSize);

    const FileStream fs(patchArc, L"rb");
    fs.SetPos(segment->Start);

    if (segment->IsCompressed)
    {
        std::vector<BYTE> compressedData(segment->ArcSize);
        fs.ReadBytes(compressedData.data(), compressedData.size());

        DWORD originalSize = data.size();
        ZLIB_uncompress(data.data(), &originalSize, compressedData.data(), compressedData.size());
    }
    else
    {
        fs.ReadBytes(data.data(), data.size());
    }
}
