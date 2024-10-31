#pragma once

class WafflePatcher
{
public:
    static void             Patch                       ();
    static void             Unpatch                     ();

private:
    static BOOL APIENTRY    PatchGetTextExtentPoint32A  (HDC hdc, LPCSTR lpString, int c, LPSIZE lpsz);
    //static void             PatchProtectedExeEncode();

    static inline decltype(GetTextExtentPoint32A)* OriginalGetTextExtentPoint32A;
};
