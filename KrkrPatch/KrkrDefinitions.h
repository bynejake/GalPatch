#pragma once

class tTJSBinaryStream
{
public:
    virtual tjs_uint64  TJS_INTF_METHOD Seek            (tjs_int64 offset, tjs_int whence) = 0;
    virtual tjs_uint    TJS_INTF_METHOD Read            (void* buffer, tjs_uint read_size) = 0;
    virtual tjs_uint    TJS_INTF_METHOD Write           (const void* buffer, tjs_uint write_size) = 0;
    virtual void        TJS_INTF_METHOD SetEndOfStorage () = 0;
    virtual tjs_uint64  TJS_INTF_METHOD GetSize         () = 0;

    virtual ~tTJSBinaryStream() = default;

    using VType = CompilerHelper::VType;
    static tTJSBinaryStream* ApplyWrapVTable(tTJSBinaryStream* pStream)
    {
        CompilerHelper::ApplyWrapVTable
            <VType::Member,
             VType::Member,
             VType::Member,
             VType::Member,
             VType::Member,
             VType::Destructor>
            (pStream);
        return pStream;
    }
};

struct XP3ArchiveSegment
{
    tjs_uint64  Start;
    tjs_uint64  Offset;
    tjs_uint64  OrgSize;
    tjs_uint64  ArcSize;
    bool        IsCompressed;
};

#pragma pack(push, 4)
class tTVPXP3ArchiveStreamBorland : public tTJSBinaryStream
{
public:
    void*                           Owner;
    tjs_int                         StorageIndex;
    std::vector<XP3ArchiveSegment>* Segments;
    tTJSBinaryStream*               Stream;
    tjs_uint64                      OrgSize;
    tjs_int                         CurSegmentNum;
    XP3ArchiveSegment*              CurSegment;
    tjs_int                         LastOpenedSegmentNum;
    tjs_uint64                      CurPos;
    tjs_uint64                      SegmentRemain;
    tjs_uint64                      SegmentPos;
    void*                           SegmentData;
    bool                            SegmentOpened;
};
#pragma pack(pop)

class tTVPXP3ArchiveStreamMsvc : public tTJSBinaryStream
{
public:
    void*                           Owner;
    tjs_int                         StorageIndex;
    std::vector<XP3ArchiveSegment>* Segments;
    tTJSBinaryStream*               Stream;
    tjs_uint64                      OrgSize;
    tjs_int                         CurSegmentNum;
    XP3ArchiveSegment*              CurSegment;
    tjs_int                         LastOpenedSegmentNum;
    tjs_uint64                      CurPos;
    tjs_uint64                      SegmentRemain;
    tjs_uint64                      SegmentPos;
    void*                           SegmentData;
    bool                            SegmentOpened;
};
