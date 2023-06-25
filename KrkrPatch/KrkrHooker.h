#pragma once

class KrkrHooker
{
public:
	static void				Hook			(const std::function<BOOL(HMODULE)>& beforeV2LinkCallback, const std::function<void()>& afterV2LinkCallback);
	static void				Unhook			();

private:
	static void				LoadLibCallback	(HMODULE hModule);

	static BOOL		WINAPI	HookImageUnload	(PLOADED_IMAGE pLoadedImage);
	static HRESULT	WINAPI	HookV2Link		(iTVPFunctionExporter* pExporter);

	static inline decltype(HookImageUnload)*	OriginalImageUnload;
	static inline decltype(HookV2Link)*			OriginalV2Link;

	static inline std::function<BOOL(HMODULE)>	BeforeV2LinkCallback;
	static inline std::function<void()>			AfterV2LinkCallback;
};
