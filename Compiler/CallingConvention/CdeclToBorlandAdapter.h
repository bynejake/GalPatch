#pragma once

template <typename TResult, auto** TFuncPtrPtr, int TFuncPtrIndex, typename... TArgs>
class CdeclToBorlandAdapterBase
{
public:
    static void Call();

private:
    static constexpr auto   FuncPtrPtr              = TFuncPtrPtr + TFuncPtrIndex;

    static constexpr int    NumCdeclStackArgs       = sizeof...(TArgs);
    static constexpr int    CdeclStackArgsSize      = NumCdeclStackArgs * 4;

    static constexpr int    NumBorlandStackArgs     = sizeof...(TArgs) > 3 ? sizeof...(TArgs) - 3 : 0;
    static constexpr int    BorlandStackArgsSize    = NumBorlandStackArgs * 4;
};

template <typename TResult, auto** TFuncPtrPtr, int TFuncPtrIndex, typename... TArgs>
__declspec(naked) void CdeclToBorlandAdapterBase<TResult, TFuncPtrPtr, TFuncPtrIndex, TArgs...>::Call()
{
    __asm
    {
        push esi
        push edi
    }
    if constexpr (sizeof...(TArgs) > 3)
    {
        __asm
        {
            lea esi, [esp + 8 + 4]
            mov edi, NumBorlandStackArgs

            nextStackArg :
            push dword ptr[esi]
            add esi, 4
            dec edi
            jnz nextStackArg
        }
    }
    if constexpr (sizeof...(TArgs) > 2)
    {
        __asm push ecx
    }
    if constexpr (sizeof...(TArgs) > 1)
    {
        __asm push edx
    }
    if constexpr (sizeof...(TArgs) > 0)
    {
        __asm push eax
    }
    __asm
    {
        mov edi, FuncPtrPtr
        call dword ptr[edi]
    }
    if constexpr (sizeof...(TArgs) > 0)
    {
        __asm add esp, CdeclStackArgsSize
    }
    __asm
    {
        pop edi
        pop esi
    }
    if constexpr (sizeof...(TArgs) > 3)
    {
        __asm
        {
            pop edx
            add esp, BorlandStackArgsSize
            jmp edx
        }
    }
    else
    {
        __asm
        {
            ret
        }
    }
}

template <typename TSign, auto** TFuncPtrPtr, int TFuncPtrIndex = 0>
class CdeclToBorlandAdapter;

template <typename TResult, auto** TFuncPtrPtr, int TFuncPtrIndex, typename... TArgs>
class CdeclToBorlandAdapter<TResult(TArgs...), TFuncPtrPtr, TFuncPtrIndex> : public CdeclToBorlandAdapterBase<TResult, TFuncPtrPtr, TFuncPtrIndex, TArgs...>
{
};
