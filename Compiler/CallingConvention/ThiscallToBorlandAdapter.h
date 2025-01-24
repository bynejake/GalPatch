#pragma once

template <typename TResult, auto** TFuncPtrPtr, size_t TFuncPtrIndex, typename... TArgs>
class ThiscallToBorlandAdapterBase
{
    static_assert(sizeof...(TArgs) > 0);

public:
    static void Call();

private:
    static constexpr auto   FuncPtrPtr              = TFuncPtrPtr + TFuncPtrIndex;

    static constexpr size_t NumThiscallStackArgs    = sizeof...(TArgs) - 1;
    static constexpr size_t ThiscallStackArgsSize   = NumThiscallStackArgs * 4;

    static constexpr size_t NumBorlandStackArgs     = sizeof...(TArgs) > 3 ? sizeof...(TArgs) - 3 : 0;
    static constexpr size_t BorlandStackArgsSize    = NumBorlandStackArgs * 4;
};

template <typename TResult, auto** TFuncPtrPtr, size_t TFuncPtrIndex, typename... TArgs>
__declspec(naked) void ThiscallToBorlandAdapterBase<TResult, TFuncPtrPtr, TFuncPtrIndex, TArgs...>::Call()
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
    __asm
    {
        mov ecx, eax
        mov edi, FuncPtrPtr
        call dword ptr[edi]
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

template <typename TSign, auto** TFuncPtrPtr, size_t TFuncPtrIndex = 0>
class ThiscallToBorlandAdapter;

template <typename TResult, auto** TFuncPtrPtr, size_t TFuncPtrIndex, typename... TArgs>
class ThiscallToBorlandAdapter<TResult(TArgs...), TFuncPtrPtr, TFuncPtrIndex> : public ThiscallToBorlandAdapterBase<TResult, TFuncPtrPtr, TFuncPtrIndex, TArgs...> {};
