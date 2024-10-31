#include "pch.h"

BOOL KrkrPatcher::PatchSignVerify(HMODULE hModule)
{
    switch (CompilerHelper::CompilerType)
    {
    case CompilerType::Msvc:
    {
        if (OriginalSignVerifyMsvc == nullptr)
        {
            static constexpr auto PATTERN_SIGN_VERIFY_MSVC = "\x57\x8B\xF9\x8B\x8F\x80\x2A\x2A\x2A\x85\xC9\x75\x2A\x68\x2A\x2A\x2A\x2A\x8B\xCF\xE8\x2A\x2A\x2A\x2A\x5F\xC3";

            OriginalSignVerifyMsvc = reinterpret_cast<decltype(PatchSignVerifyMsvc)*>(Pe::FindData(hModule, PATTERN_SIGN_VERIFY_MSVC, strlen(PATTERN_SIGN_VERIFY_MSVC)));
            if (OriginalSignVerifyMsvc != nullptr)
            {
                LOG(L"KrkrPatch: PatchSignVerify Msvc success!");

                DetoursHelper::Hook(std::pair(&OriginalSignVerifyMsvc, PatchSignVerifyMsvc));
                return TRUE;
            }
        }
    }
    return FALSE;
    default:
        return TRUE;
    }
}

void KrkrPatcher::PatchCreateStream()
{
    switch (CompilerHelper::CompilerType)
    {
    case CompilerType::Borland:
    {
        static constexpr auto PATTERN_CREATE_STREAM_BORLAND = "\x55\x8B\xEC\x81\xC4\x60\xFF\xFF\xFF\x53\x56\x57\x89\x95\x6C\xFF\xFF\xFF\x89\x85\x70\xFF\xFF\xFF\xB8\x2A\x2A\x2A\x2A\xC7\x85\x7C\xFF\xFF\xFF\x2A\x2A\x2A\x2A\x89\x65\x80\x89\x85\x78\xFF\xFF\xFF\x66\xC7\x45\x84\x2A\x2A\x33\xD2\x89\x55\x90\x64\x8B\x0D\x2A\x2A\x2A\x2A\x89\x8D\x74\xFF\xFF\xFF\x8D\x85\x74\xFF\xFF\xFF\x64\xA3\x2A\x2A\x2A\x2A\x66\xC7\x45\x84\x08\x2A\x8B\x95\x6C\xFF\xFF\xFF\x8B\x85\x70\xFF\xFF\xFF\xE8\x2A\x2A\x2A\x2A\x8B\x95\x74\xFF\xFF\xFF\x64\x89\x15\x2A\x2A\x2A\x2A\xE9\x2A\x06\x2A\x2A";

        OriginalCreateStreamBorland = reinterpret_cast<decltype(PatchCreateStreamBorland)*>(Pe::FindData(PATTERN_CREATE_STREAM_BORLAND, strlen(PATTERN_CREATE_STREAM_BORLAND)));
        if (OriginalCreateStreamBorland != nullptr)
        {
            LOG(L"KrkrPatch: PatchCreateStream Borland success!");

            DetoursHelper::Hook(std::pair(&OriginalCreateStreamBorland, CompilerHelper::WrapAsStaticFunc<tTJSBinaryStream*, PatchCreateStreamBorland, const ttstr&, tjs_uint32>()));
            return;
        }

        throw std::exception("PatchCreateStream Borland fail!");
    }
    case CompilerType::Msvc:
    {
        static constexpr auto PATTERN_CREATE_STREAM_MSVC = "\x55\x8B\xEC\x6A\xFF\x68\x2A\x2A\x2A\x2A\x64\xA1\x2A\x2A\x2A\x2A\x50\x83\xEC\x5C\x53\x56\x57\xA1\x2A\x2A\x2A\x2A\x33\xC5\x50\x8D\x45\xF4\x64\xA3\x2A\x2A\x2A\x2A\x89\x65\xF0\x89\x4D\xEC\xC7\x45\xFC\x2A\x2A\x2A\x2A\xE8\x2A\x2A\x2A\x2A\x8B\x4D\xF4\x64\x89\x0D\x2A\x2A\x2A\x2A\x59\x5F\x5E\x5B\x8B\xE5\x5D\xC3";

        OriginalCreateStreamMsvc = reinterpret_cast<decltype(PatchCreateStreamMsvc)*>(Pe::FindData(PATTERN_CREATE_STREAM_MSVC, strlen(PATTERN_CREATE_STREAM_MSVC)));
        if (OriginalCreateStreamMsvc != nullptr)
        {
            LOG(L"KrkrPatch: PatchCreateStream Msvc success!");

            DetoursHelper::Hook(std::pair(&OriginalCreateStreamMsvc, PatchCreateStreamMsvc));
            return;
        }

        throw std::exception("PatchCreateStream Msvc fail!");
    }
    default:
        break;
    }
}

void KrkrPatcher::Unpatch()
{
    if (OriginalSignVerifyMsvc != nullptr)
    {
        DetoursHelper::Unhook(std::pair(&OriginalSignVerifyMsvc, PatchSignVerifyMsvc));
        OriginalSignVerifyMsvc = nullptr;
    }

    if (OriginalCreateStreamBorland != nullptr)
    {
        DetoursHelper::Unhook(std::pair(&OriginalCreateStreamBorland, PatchCreateStreamBorland));
        OriginalCreateStreamBorland = nullptr;
    }

    if (OriginalCreateStreamMsvc != nullptr)
    {
        DetoursHelper::Unhook(std::pair(&OriginalCreateStreamMsvc, PatchCreateStreamMsvc));
        OriginalCreateStreamMsvc = nullptr;
    }
}

BOOL KrkrPatcher::PatchSignVerifyMsvc(HMODULE hModule)
{
    return TRUE;
}

tTJSBinaryStream* KrkrPatcher::PatchCreateStreamBorland(const ttstr& name, tjs_uint32 flags)
{
    return PatchCreateStream<tTVPXP3ArchiveStreamBorland, &OriginalCreateStreamBorland>(name, flags);
}

tTJSBinaryStream* KrkrPatcher::PatchCreateStreamMsvc(const ttstr& name, tjs_uint32 flags)
{
    return PatchCreateStream<tTVPXP3ArchiveStreamMsvc, &OriginalCreateStreamMsvc>(name, flags);
}

template <typename TArcStream, auto** TOriginalCreateStream>
tTJSBinaryStream* KrkrPatcher::PatchCreateStream(const ttstr& name, tjs_uint32 flags)
{
    const auto [patchUrl, patchArc] = PatchUrl(name, flags);
    const auto patchUrlStream = CompilerHelper::CallStaticFunc<tTJSBinaryStream*, TOriginalCreateStream, const ttstr&, tjs_uint32>(patchUrl.c_str(), flags);

    if (!patchArc.empty())
    {
        XP3ArchiveSegment* segment;
        if (std::is_same_v<TArcStream, tTVPXP3ArchiveStreamBorland>)
            segment = reinterpret_cast<tTVPXP3ArchiveStreamBorland*>(patchUrlStream)->CurSegment;
        else if (std::is_same_v<TArcStream, tTVPXP3ArchiveStreamMsvc>)
            segment = reinterpret_cast<tTVPXP3ArchiveStreamMsvc*>(patchUrlStream)->CurSegment;
        else
            throw std::exception("Unsupported CompilerType!");

        const auto patchArcStream = new KrkrPatchArcStream(patchArc, segment);
        tTJSBinaryStream::ApplyWrapVTable(patchArcStream);
        return patchArcStream;
    }

    return patchUrlStream;
}

std::pair<std::wstring, std::wstring> KrkrPatcher::PatchUrl(const ttstr& name, tjs_uint32 flags)
{
    if (flags == TJS_BS_READ)
    {
        LOG(L"KrkrPatch: PatchUrl direct {}", name.c_str());

        if (const auto patchName = PatchName(name); !patchName.empty())
        {
            static const auto [PatchDirs, PatchArcs] = PatchPathes();

            for (auto& patchDir : PatchDirs)
            {
                if (const auto patchUrl = patchDir + L"\\" + patchName; TVPIsExistentStorageNoSearch(patchUrl.c_str()))
                {
                    LOG(L"KrkrPatch: PatchUrl redirect {}", patchUrl);
                    return {patchUrl, L""};
                }
            }

            for (auto& patchArc : PatchArcs)
            {
                if (const auto patchUrl = patchArc + L">" + patchName; TVPIsExistentStorageNoSearch(patchUrl.c_str()))
                {
                    LOG(L"KrkrPatch: PatchUrl redirect {}", patchUrl);
                    return {patchUrl, patchArc};
                }
            }

            // temp for test
            /*LOG(L"KrkrPatch: PatchUrl org {}", name.c_str());
            std::wstring a = name.c_str();
            if (a.starts_with(L"arc://./") || !a.starts_with(L"file://./"))
            {
                const auto stream = CompilerHelper::CallStaticFunc<tTJSBinaryStream*, &OriginalCreateStreamMsvc, const ttstr&, tjs_uint32>(name.c_str(), flags);
                const auto b = PatchName(name);

                std::vector<BYTE> data;
                data.resize(stream->GetSize());
                stream->Read(data.data(), data.size());
                stream->Seek(0, SEEK_SET);

                decrypt(stream, data);

                const auto filePath = PathUtil::GetAppPath() + L"dump\\" + b;

                LOG(L"KrkrPatch: PatchUrl dump {}", filePath);

                FileStream fileStream(filePath, L"wb+");
                fileStream.WriteBytes(data.data(), data.size());
            }*/
        }
    }

    return {name.c_str(), L""};
}

// temp for test
//void KrkrPatcher::decrypt(tTJSBinaryStream* stream, std::vector<BYTE>& output)
//{
//    try
//    {
//        uint8_t mark[2];
//
//        memset(mark, 0, sizeof(mark));
//        stream->Read(mark, 2);
//
//        if (mark[0] == 0xfe && mark[1] == 0xfe)
//        {
//            uint8_t mode;
//
//            stream->Read(&mode, 1);
//
//            if (mode != 0 && mode != 1 && mode != 2)
//            {
//                return;
//            }
//
//            memset(mark, 0, sizeof(mark));
//            stream->Read(mark, 2);
//
//            if (mark[0] != 0xff || mark[1] != 0xfe)
//            {
//                return;
//            }
//
//            if (mode == 2)
//            {
//                tjs_int64 compressed = 0;
//                tjs_int64 uncompressed = 0;
//
//                stream->Read(&compressed, sizeof(tjs_int64));
//                stream->Read(&uncompressed, sizeof(tjs_int64));
//
//                if (compressed <= 0 || compressed >= INT_MAX || uncompressed <= 0 || uncompressed >= INT_MAX)
//                {
//                    return;
//                }
//
//                std::vector<uint8_t> data((size_t)compressed);
//
//                if (stream->Read(data.data(), (tjs_uint)compressed) != compressed)
//                {
//                    return;
//                }
//
//                size_t count = (size_t)uncompressed;
//
//                std::vector<uint8_t> buffer(count + 2);
//
//                buffer[0] = mark[0];
//                buffer[1] = mark[1];
//
//                BYTE* dest = buffer.data() + 2;
//                DWORD destLen = uncompressed;
//
//                int result = 0;
//
//                try
//                {
//                    result = ZLIB_uncompress(dest, &destLen, data.data(), (LONG64)compressed);
//                }
//                catch (...)
//                {
//                    return;
//                }
//
//                if (result != 0 || destLen != uncompressed)
//                {
//                    return;
//                }
//
//                output = std::move(buffer);
//            }
//            else
//            {
//                tjs_int64 startpos = (tjs_int64)stream->Seek(0, TJS_BS_SEEK_CUR);
//                tjs_int64 endpos = (tjs_int64)stream->Seek(0, TJS_BS_SEEK_END);
//
//                stream->Seek(startpos, TJS_BS_SEEK_SET);
//
//                tjs_int64 size = endpos - startpos;
//
//                if (size <= 0 || size >= INT_MAX)
//                {
//                    return;
//                }
//
//                size_t count = (size_t)(size / sizeof(tjs_char));
//
//                if (count == 0)
//                {
//                    return;
//                }
//
//                std::vector<tjs_char> buffer(count);
//
//                tjs_uint sizeToRead = (tjs_uint)size;
//
//                stream->Read(buffer.data(), sizeToRead);
//
//                if (mode == 0)
//                {
//                    for (size_t i = 0; i < count; i++)
//                    {
//                        tjs_char ch = buffer[i];
//                        if (ch >= 0x20) buffer[i] = ch ^ (((ch & 0xfe) << 8) ^ 1);
//                    }
//                }
//                else if (mode == 1)
//                {
//                    for (size_t i = 0; i < count; i++)
//                    {
//                        tjs_char ch = buffer[i];
//                        ch = ((ch & 0xaaaaaaaa) >> 1) | ((ch & 0x55555555) << 1);
//                        buffer[i] = ch;
//                    }
//                }
//
//                size_t sizeToCopy = count * sizeof(tjs_char);
//
//                output.resize(sizeToCopy + 2);
//
//                output[0] = mark[0];
//                output[1] = mark[1];
//
//                memcpy(output.data() + 2, buffer.data(), sizeToCopy);
//            }
//        }
//    }
//    catch (...)
//    {
//    }
//}

std::wstring KrkrPatcher::PatchName(const ttstr& name)
{
    std::wstring patchName = name.c_str();

    auto pos = std::wstring::npos;
    if (patchName.starts_with(L"archive://./") || patchName.starts_with(L"arc://./"))
        pos = patchName.find_last_of(L'/') + 1;
    else if (patchName.starts_with(L"file://./") && patchName.contains(L".xp3>"))
        pos = patchName.find_last_of(L"/>") + 1;
    else if (!patchName.contains(L':'))
        pos = 0;

    patchName.erase(0, pos);
    return patchName;
}

std::pair<std::vector<std::wstring>, std::vector<std::wstring>> KrkrPatcher::PatchPathes()
{
    const auto appPath = PathUtil::GetAppPath();

    std::vector<std::wstring> patchDirs;
    std::vector<std::wstring> patchArcs;

    static constexpr auto PATCH_COUNT = 9;
    for (int num = PATCH_COUNT; num > 0; --num)
    {
        const auto patchPathPrefix = appPath + L"unencrypted" + (num == 1 ? L"" : std::to_wstring(num));

        if (const auto patchDir = patchPathPrefix; GetFileAttributes(patchDir.c_str()) == FILE_ATTRIBUTE_DIRECTORY)
            patchDirs.emplace_back(patchDir);

        if (const auto patchArc = patchPathPrefix + L".xp3"; GetFileAttributes(patchArc.c_str()) == FILE_ATTRIBUTE_ARCHIVE)
            patchArcs.emplace_back(patchArc);
    }

    return {patchDirs, patchArcs};
}
