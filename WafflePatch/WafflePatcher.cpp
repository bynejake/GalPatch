#include "pch.h"

using namespace std;

void WafflePatcher::Patch()
{
    if (OriginalGetTextExtentPoint32A != nullptr)
        return;

    OriginalGetTextExtentPoint32A = GetTextExtentPoint32A;
    DetoursHelper::Hook(pair(&OriginalGetTextExtentPoint32A, PatchGetTextExtentPoint32A));
}

void WafflePatcher::Unpatch()
{
    if (OriginalGetTextExtentPoint32A == nullptr)
        return;

    DetoursHelper::Unhook(pair(&OriginalGetTextExtentPoint32A, PatchGetTextExtentPoint32A));
    OriginalGetTextExtentPoint32A = nullptr;
}

BOOL WafflePatcher::PatchGetTextExtentPoint32A(HDC hdc, LPCSTR lpString, int c, LPSIZE lpsz)
{
    if (strcmp(lpString, "\t") == 0)
        lpString = " ";

    return OriginalGetTextExtentPoint32A(hdc, lpString, c, lpsz);
}
