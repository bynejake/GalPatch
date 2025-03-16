#pragma once

class KrkrPatchStream : public tTJSBinaryStream
{
public:
    ~KrkrPatchStream() override = default;

    tjs_uint64  TJS_INTF_METHOD Seek            (tjs_int64 offset, tjs_int whence) final;
    tjs_uint    TJS_INTF_METHOD Read            (       void* buffer, tjs_uint read_size) final;
    tjs_uint    TJS_INTF_METHOD Write           (const  void* buffer, tjs_uint write_size) final;
    void        TJS_INTF_METHOD SetEndOfStorage () final;
    tjs_uint64  TJS_INTF_METHOD GetSize         () final;

protected:
    std::vector<BYTE> data;

private:
    tjs_uint64 pos = 0;
};

class KrkrPatchSigStream final : public KrkrPatchStream
{
public:
    KrkrPatchSigStream();
};

class KrkrPatchArcStream final : public KrkrPatchStream
{
public:
    KrkrPatchArcStream(const std::wstring& patchArc, const XP3ArchiveSegment* segment);
};
