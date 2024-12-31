#pragma once

class WafflePatcher
{
public:
#ifdef PROTECTED_EXE
    static void             PatchProtectedExeEncoding();
#endif // PROTECTED_EXE
    static void             PatchGetTextCrash           ();
    static void             Unpatch                     ();

private:
    static BOOL APIENTRY    PatchGetTextExtentPoint32A  (HDC hdc, LPCSTR lpString, int c, LPSIZE lpsz);

    static inline decltype(GetTextExtentPoint32A)* OriginalGetTextExtentPoint32A;
};
