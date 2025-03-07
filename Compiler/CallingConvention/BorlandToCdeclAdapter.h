#pragma once

template <typename TResult, auto** TFuncPtrPtr, size_t TFuncPtrIndex, typename... TArgs>
class BorlandToCdeclAdapterBase
{
public:
    static TResult Call(TArgs...);

private:
    static constexpr auto   FuncPtrPtr              = TFuncPtrPtr + TFuncPtrIndex;

    static constexpr size_t NumBorlandStackArgs     = sizeof...(TArgs) > 3 ? sizeof...(TArgs) - 3 : 0;
    static constexpr size_t BorlandStackArgsSize    = NumBorlandStackArgs * 4;

    static constexpr size_t NumCdeclStackArgs       = sizeof...(TArgs);
    static constexpr size_t CdeclStackArgsSize      = NumCdeclStackArgs * 4;
};

template <typename TResult, auto** TFuncPtrPtr, size_t TFuncPtrIndex, typename... TArgs>
__declspec(naked) TResult BorlandToCdeclAdapterBase<TResult, TFuncPtrPtr, TFuncPtrIndex, TArgs...>::Call(TArgs...)
{
    __asm
    {
        push esi
        push edi
    }
    if constexpr (sizeof...(TArgs) > 0)
    {
        __asm mov eax, [esp + 8 + 4]
    }
    if constexpr (sizeof...(TArgs) > 1)
    {
        __asm mov edx, [esp + 8 + 8]
    }
    if constexpr (sizeof...(TArgs) > 2)
    {
        __asm mov ecx, [esp + 8 + 0xC]
    }
    if constexpr (sizeof...(TArgs) > 3)
    {
        __asm
        {
            lea esi, [esp + 8 + 0x10]
            mov edi, NumBorlandStackArgs

            nextStackArg :
            push dword ptr[esi]
            add esi, 4
            dec edi
            jnz nextStackArg
        }
    }
    __asm
    {
        mov edi, FuncPtrPtr
        call dword ptr[edi]
        pop edi
        pop esi
        ret
    }
}

template <typename TSign, auto** TFuncPtrPtr, size_t TFuncPtrIndex = 0>
class BorlandToCdeclAdapter;

template <typename TResult, auto** TFuncPtrPtr, size_t TFuncPtrIndex, typename... TArgs>
class BorlandToCdeclAdapter<TResult(TArgs...), TFuncPtrPtr, TFuncPtrIndex> : public BorlandToCdeclAdapterBase<TResult, TFuncPtrPtr, TFuncPtrIndex, TArgs...> {};
