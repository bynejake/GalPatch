#include "DetoursHelper.h"

BOOL DetoursHelper::FindExport(HMODULE hModule, LPCSTR pszName)
{
	return FindExportEx(hModule, pszName) != nullptr;
}

PVOID DetoursHelper::FindExportEx(HMODULE hModule, LPCSTR pszName)
{
	if (pszName == nullptr)
		return nullptr;

	FindExportContext findExportContext
	{
		.pszName = pszName
	};
	DetourEnumerateExports(hModule, &findExportContext, CheckExport);
	return findExportContext.pvFunc;
}

BOOL DetoursHelper::FindImport(HMODULE hModule, LPCSTR pszName)
{
	return FindImportEx(hModule, pszName) != nullptr;
}

PVOID* DetoursHelper::FindImportEx(HMODULE hModule, LPCSTR pszName)
{
	if (pszName == nullptr)
		return nullptr;

	FindImportContext findImportContext
	{
		.pszName = pszName
	};
	DetourEnumerateImportsEx(hModule, &findImportContext, nullptr, CheckImport);
	return findImportContext.ppvFunc;
}

BOOL DetoursHelper::CheckExport(PVOID pContext, DWORD nOrdinal, LPCSTR pszName, PVOID pvFunc)
{
	if (const auto pFindExportContext = static_cast<FindExportContext*>(pContext); pszName != nullptr && strcmp(pFindExportContext->pszName, pszName) == 0)
	{
		pFindExportContext->pvFunc = pvFunc;
		return FALSE;
	}
	return TRUE;
}

BOOL DetoursHelper::CheckImport(PVOID pContext, DWORD nOrdinal, LPCSTR pszName, PVOID* ppvFunc)
{
	if (const auto pFindImportContext = static_cast<FindImportContext*>(pContext); pszName != nullptr && strcmp(pFindImportContext->pszName, pszName) == 0)
	{
		pFindImportContext->ppvFunc = ppvFunc;
		return FALSE;
	}
	return TRUE;
}
