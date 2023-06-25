#include "pch.h"

using namespace std;

BOOL KrkrPatcher::PatchSignVerify(HMODULE hModule)
{
	switch (CompilerHelper::CompilerType)
	{
	case CompilerType::Msvc:
		{
			if (!OriginalSignVerifyMsvc)
			{
				static constexpr auto SIGN_VERIFY_MSVC =
					"\x57\x8B\xF9\x8B\x8F\x80\x2A\x2A\x2A\x85\xC9\x75\x2A\x68\x2A\x2A\x2A\x2A\x8B\xCF\xE8\x2A\x2A\x2A\x2A\x5F\xC3";

				OriginalSignVerifyMsvc = reinterpret_cast<decltype(PatchSignVerifyMsvc)*>(PE::FindData(hModule, SIGN_VERIFY_MSVC, strlen(SIGN_VERIFY_MSVC)));
				if (OriginalSignVerifyMsvc)
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
		static constexpr auto PATTERN_CREATE_STREAM_BORLAND =
			"\x55\x8B\xEC\x81\xC4\x60\xFF\xFF\xFF\x53\x56\x57\x89\x95\x6C\xFF\xFF\xFF\x89\x85\x70\xFF\xFF\xFF\xB8\x2A\x2A\x2A\x2A\xC7\x85\x7C\xFF\xFF\xFF\x2A\x2A\x2A\x2A\x89\x65\x80\x89\x85\x78\xFF\xFF\xFF\x66\xC7\x45\x84\x2A\x2A\x33\xD2\x89\x55\x90\x64\x8B\x0D\x2A\x2A\x2A\x2A\x89\x8D\x74\xFF\xFF\xFF\x8D\x85\x74\xFF\xFF\xFF\x64\xA3\x2A\x2A\x2A\x2A\x66\xC7\x45\x84\x08\x2A\x8B\x95\x6C\xFF\xFF\xFF\x8B\x85\x70\xFF\xFF\xFF\xE8\x2A\x2A\x2A\x2A\x8B\x95\x74\xFF\xFF\xFF\x64\x89\x15\x2A\x2A\x2A\x2A\xE9\x2A\x06\x2A\x2A";

		OriginalCreateStreamBorland = reinterpret_cast<decltype(PatchCreateStreamBorland)*>(PE::FindData(PATTERN_CREATE_STREAM_BORLAND, strlen(PATTERN_CREATE_STREAM_BORLAND)));
		if (OriginalCreateStreamBorland)
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
			static constexpr auto PATTERN_CREATE_STREAM_MSVC =
				"\x55\x8B\xEC\x6A\xFF\x68\x2A\x2A\x2A\x2A\x64\xA1\x2A\x2A\x2A\x2A\x50\x83\xEC\x5C\x53\x56\x57\xA1\x2A\x2A\x2A\x2A\x33\xC5\x50\x8D\x45\xF4\x64\xA3\x2A\x2A\x2A\x2A\x89\x65\xF0\x89\x4D\xEC\xC7\x45\xFC\x2A\x2A\x2A\x2A\xE8\x2A\x2A\x2A\x2A\x8B\x4D\xF4\x64\x89\x0D\x2A\x2A\x2A\x2A\x59\x5F\x5E\x5B\x8B\xE5\x5D\xC3";

			OriginalCreateStreamMsvc = reinterpret_cast<decltype(PatchCreateStreamMsvc)*>(PE::FindData(PATTERN_CREATE_STREAM_MSVC, strlen(PATTERN_CREATE_STREAM_MSVC)));
			if (OriginalCreateStreamMsvc)
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

void KrkrPatcher::Unpatch()
{
	// TODO what?
}

BOOL KrkrPatcher::PatchSignVerifyMsvc(HMODULE hModule)
{
	return TRUE;
}

tTJSBinaryStream* KrkrPatcher::PatchCreateStreamBorland(const ttstr& name, tjs_uint32 flags)
{
	return CompilerHelper::CallStaticFunc<tTJSBinaryStream*, &OriginalCreateStreamBorland, const ttstr&, tjs_uint32>(PatchUrl(name).c_str(), flags);
}

tTJSBinaryStream* KrkrPatcher::PatchCreateStreamMsvc(const ttstr& name, tjs_uint32 flags)
{
	return OriginalCreateStreamMsvc(PatchUrl(name).c_str(), flags);
}

wstring KrkrPatcher::PatchUrl(const ttstr& name)
{
	spdlog::debug(L"PatchUrl {}", name.c_str());

	static const auto DIRECTORY = PathUtil::GetAppPath() + L"patch\\";
	if (GetFileAttributes(DIRECTORY.c_str()) == FILE_ATTRIBUTE_DIRECTORY)
	{
		wstring _name = name.c_str();

		auto pos = wstring::npos;
		if (_name.starts_with(L"archive://./") || _name.starts_with(L"arc://./"))
			pos = _name.find_last_of(L'/') + 1;
		else if (_name.starts_with(L"file://./") && _name.contains(L".xp3>"))
			pos = max(_name.find_last_of(L'/'), _name.find_last_of(L'>')) + 1;
		else if (!_name.contains(L':'))
			pos = 0;

		_name.erase(0, pos);

		auto url = DIRECTORY + _name;
		if (TVPIsExistentStorageNoSearch(url.c_str()))
		{
			spdlog::info(L"PatchUrl {} to {}", name.c_str(), url);
			return url;
		}
	}
	return name.c_str();
}
