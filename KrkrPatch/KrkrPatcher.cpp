#include "pch.h"

using namespace std;

BOOL KrkrPatcher::PatchSignVerify(HMODULE hModule)
{
    switch (CompilerHelper::CompilerType)
    {
    case CompilerType::Msvc:
    {
        if (OriginalSignVerifyMsvc == nullptr)
        {
            static constexpr auto PATTERN_SIGN_VERIFY_MSVC = "\x57\x8B\xF9\x8B\x8F\x80\x2A\x2A\x2A\x85\xC9\x75\x2A\x68\x2A\x2A\x2A\x2A\x8B\xCF\xE8\x2A\x2A\x2A\x2A\x5F\xC3";

            OriginalSignVerifyMsvc = reinterpret_cast<decltype(PatchSignVerifyMsvc)*>(PE::FindData(hModule, PATTERN_SIGN_VERIFY_MSVC, strlen(PATTERN_SIGN_VERIFY_MSVC)));
            if (OriginalSignVerifyMsvc != nullptr)
            {
                spdlog::info("PatchSignVerify Msvc success!");
                DetoursHelper::Hook(pair(&OriginalSignVerifyMsvc, PatchSignVerifyMsvc));
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

        OriginalCreateStreamBorland = reinterpret_cast<decltype(PatchCreateStreamBorland)*>(PE::FindData(PATTERN_CREATE_STREAM_BORLAND, strlen(PATTERN_CREATE_STREAM_BORLAND)));
        if (OriginalCreateStreamBorland != nullptr)
        {
            spdlog::info("PatchCreateStream Borland success");
            DetoursHelper::Hook(pair(&OriginalCreateStreamBorland, CompilerHelper::WrapAsStaticFunc<tTJSBinaryStream*, PatchCreateStreamBorland, const ttstr&, tjs_uint32>()));
            return;
        }

        spdlog::error("PatchCreateStream Borland fail");
    }
    break;
    case CompilerType::Msvc:
    {
        static constexpr auto PATTERN_CREATE_STREAM_MSVC = "\x55\x8B\xEC\x6A\xFF\x68\x2A\x2A\x2A\x2A\x64\xA1\x2A\x2A\x2A\x2A\x50\x83\xEC\x5C\x53\x56\x57\xA1\x2A\x2A\x2A\x2A\x33\xC5\x50\x8D\x45\xF4\x64\xA3\x2A\x2A\x2A\x2A\x89\x65\xF0\x89\x4D\xEC\xC7\x45\xFC\x2A\x2A\x2A\x2A\xE8\x2A\x2A\x2A\x2A\x8B\x4D\xF4\x64\x89\x0D\x2A\x2A\x2A\x2A\x59\x5F\x5E\x5B\x8B\xE5\x5D\xC3";

        OriginalCreateStreamMsvc = reinterpret_cast<decltype(PatchCreateStreamMsvc)*>(PE::FindData(PATTERN_CREATE_STREAM_MSVC, strlen(PATTERN_CREATE_STREAM_MSVC)));
        if (OriginalCreateStreamMsvc != nullptr)
        {
            spdlog::info("PatchCreateStream Msvc success");
            DetoursHelper::Hook(pair(&OriginalCreateStreamMsvc, PatchCreateStreamMsvc));
            return;
        }

        spdlog::error("PatchCreateStream Msvc fail");
    }
    break;
    default:
        break;
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
    const auto stream = CompilerHelper::CallStaticFunc<tTJSBinaryStream*, TOriginalCreateStream, const ttstr&, tjs_uint32>(patchUrl.c_str(), flags);

    if (!patchArc.empty())
    {
        XP3ArchiveSegment* segment;
        if (is_same_v<TArcStream, tTVPXP3ArchiveStreamBorland>)
            segment = reinterpret_cast<tTVPXP3ArchiveStreamBorland*>(stream)->CurSegment;
        else if (is_same_v<TArcStream, tTVPXP3ArchiveStreamMsvc>)
            segment = reinterpret_cast<tTVPXP3ArchiveStreamMsvc*>(stream)->CurSegment;
        else
            throw exception("Unsupported CompilerType");

        const auto patchArcStream = new KrkrPatchArcStream(patchArc, segment);
        tTJSBinaryStream::ApplyWrapVTable(patchArcStream);
        return patchArcStream;
    }

    return stream;
}

pair<wstring, wstring> KrkrPatcher::PatchUrl(const ttstr& name, tjs_uint32 flags)
{
    if (flags == TJS_BS_READ)
    {
        spdlog::debug(L"PatchUrl {}", name.c_str());

        static const auto PATCH_APP = PathUtil::GetAppPath();
        static const auto PATCH_DIR = PATCH_APP + L"unencrypted\\";
        static const auto PATCH_ARC = PATCH_APP + L"unencrypted.xp3";

        if (const auto patchName = PatchName(name); !patchName.empty())
        {
            if (GetFileAttributes(PATCH_DIR.c_str()) == FILE_ATTRIBUTE_DIRECTORY)
            {
                const auto patchUrl = PATCH_DIR + patchName;
                if (TVPIsExistentStorageNoSearch(patchUrl.c_str()))
                {
                    spdlog::info(L"PatchUrl {} to {}", name.c_str(), patchUrl);
                    return { patchUrl, L"" };
                }
            }

            if (GetFileAttributes(PATCH_ARC.c_str()) == FILE_ATTRIBUTE_ARCHIVE)
            {
                const auto patchUrl = PATCH_ARC + L">" + patchName;
                if (TVPIsExistentStorageNoSearch(patchUrl.c_str()))
                {
                    spdlog::info(L"PatchUrl {} to {}", name.c_str(), patchUrl);
                    return { patchUrl, PATCH_ARC };
                }
            }
        }
    }
    return { name.c_str(), L"" };
}

wstring KrkrPatcher::PatchName(const ttstr& name)
{
    wstring patchName = name.c_str();

    auto pos = wstring::npos;
    if (patchName.starts_with(L"archive://./") || patchName.starts_with(L"arc://./"))
        pos = patchName.find_last_of(L'/') + 1;
    else if (patchName.starts_with(L"file://./") && patchName.contains(L".xp3>"))
        pos = patchName.find_last_of(L"/>") + 1;
    else if (!patchName.contains(L':'))
        pos = 0;

    patchName.erase(0, pos);
    return patchName;
}
