#pragma once

template <typename TResult, auto** TFuncPtrPtr, size_t TFuncPtrIndex, typename... TArgs>
class CdeclToThiscallAdapterBase
{
    static_assert(sizeof...(TArgs) > 0);

public:
    static void Call();

private:
    static constexpr auto   FuncPtrPtr              = TFuncPtrPtr + TFuncPtrIndex;

    static constexpr size_t NumCdeclStackArgs       = sizeof...(TArgs);
    static constexpr size_t CdeclStackArgsSize      = NumCdeclStackArgs * 4;

    static constexpr size_t NumThiscallStackArgs    = sizeof...(TArgs) - 1;
    static constexpr size_t ThiscallStackArgsSize   = NumThiscallStackArgs * 4;
};

template <typename TResult, auto** TFuncPtrPtr, size_t TFuncPtrIndex, typename... TArgs>
__declspec(naked) void CdeclToThiscallAdapterBase<TResult, TFuncPtrPtr, TFuncPtrIndex, TArgs...>::Call()
{
    if constexpr (sizeof...(TArgs) > 1)
    {
        __asm
        {
            mov eax, NumThiscallStackArgs
            lea edx, [esp + 4 + 4 * eax]

            nextStackArg:
            sub edx, 4
            push dword ptr[edx]
            dec eax
            jnz nextStackArg
        }
    }
    __asm
    {
        push ecx
        mov eax, FuncPtrPtr
        call dword ptr[eax]
        add esp, CdeclStackArgsSize
    }

    if constexpr (sizeof...(TArgs) > 1)
    {
        __asm
        {
            pop edx
            add esp, ThiscallStackArgsSize
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

template <typename TSign, auto** TFuncPtrPtr, size_t TFuncPtrIndex = 0>
class CdeclToThiscallAdapter;

template <typename TResult, auto** TFuncPtrPtr, size_t TFuncPtrIndex, typename... TArgs>
class CdeclToThiscallAdapter<TResult(TArgs...), TFuncPtrPtr, TFuncPtrIndex> : public CdeclToThiscallAdapterBase<TResult, TFuncPtrPtr, TFuncPtrIndex, TArgs...> {};
