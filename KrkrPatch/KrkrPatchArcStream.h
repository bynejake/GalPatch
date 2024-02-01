#pragma once

class KrkrPatchArcStream : public tTJSBinaryStream
{
public:
    KrkrPatchArcStream(const std::wstring& patchArc, const XP3ArchiveSegment* segment);
    ~KrkrPatchArcStream() override = default;

    tjs_uint64  TJS_INTF_METHOD Seek            (tjs_int64 offset, tjs_int whence) override;
    tjs_uint    TJS_INTF_METHOD Read            (void* buffer, tjs_uint read_size) override;
    tjs_uint    TJS_INTF_METHOD Write           (const void* buffer, tjs_uint write_size) override;
    void        TJS_INTF_METHOD SetEndOfStorage () override;
    tjs_uint64  TJS_INTF_METHOD GetSize         () override;

private:
    std::vector<BYTE>   data;
    tjs_uint64          pos;
};
