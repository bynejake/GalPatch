#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <vector>

class MemoryUtil
{
public:
    template <typename T>
    static void Write(PVOID addr, const std::vector<T>& val)
    {
        const auto size = val.size() * sizeof(T);

        PageUnprotector unprotector{addr, size};
        std::memcpy(addr, val.data(), size);
    }

private:
    class PageUnprotector
    {
    public:
        PageUnprotector(LPVOID addr, SIZE_T size)
            : addr(addr), size(size)
        {
            VirtualProtect(addr, size, PAGE_READWRITE, &originalProtect);
        }

        ~PageUnprotector()
        {
            DWORD dummy;
            VirtualProtect(addr, size, originalProtect, &dummy);
        }

    private:
        LPVOID  addr;
        SIZE_T  size;
        DWORD   originalProtect;
    };
};
