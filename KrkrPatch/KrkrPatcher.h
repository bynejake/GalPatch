#pragma once

class KrkrPatcher
{
public:
	static BOOL								PatchSignVerify			(HMODULE hModule);
	static void								PatchCreateStream		();
	static void								Unpatch					();

private:
	static BOOL					__fastcall	PatchSignVerifyMsvc		(HMODULE hModule);
	static tTJSBinaryStream*				PatchCreateStreamBorland(const ttstr& name, tjs_uint32 flags);
	static tTJSBinaryStream*	__fastcall	PatchCreateStreamMsvc	(const ttstr& name, tjs_uint32 flags);

	static std::wstring						PatchUrl				(const ttstr& name);

	static inline decltype(PatchSignVerifyMsvc)*		OriginalSignVerifyMsvc;
	static inline decltype(PatchCreateStreamBorland)*	OriginalCreateStreamBorland;
	static inline decltype(PatchCreateStreamMsvc)*		OriginalCreateStreamMsvc;
};
