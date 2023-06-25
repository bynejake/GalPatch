#pragma once

template <typename TResult, auto** TFuncPtrPtr, int TFuncPtrIndex, typename... TArgs>
class ThiscallToCdeclAdapterBase
{
	static_assert(sizeof...(TArgs) > 0);

public:
	static TResult Call(TArgs...);

private:
	static constexpr auto FuncPtrPtr			= TFuncPtrPtr + TFuncPtrIndex;

	static constexpr int NumCdeclStackArgs		= sizeof...(TArgs);
	static constexpr int CdeclStackArgsSize		= NumCdeclStackArgs * 4;

	static constexpr int NumThiscallStackArgs	= sizeof...(TArgs) - 1;
	static constexpr int ThiscallStackArgsSize	= NumThiscallStackArgs * 4;
};

template <typename TResult, auto** TFuncPtrPtr, int TFuncPtrIndex, typename... TArgs>
__declspec(naked) TResult ThiscallToCdeclAdapterBase<TResult, TFuncPtrPtr, TFuncPtrIndex, TArgs...>::Call(TArgs...)
{
	__asm
	{
		mov ecx, [esp + 4]
	}
	if constexpr (sizeof...(TArgs) > 1)
	{
		__asm
		{
			mov eax, NumThiscallStackArgs
			lea edx, [esp + 8 + 4 * eax]

			nextStackArg:
			sub edx, 4
				push dword ptr[edx]
				dec eax
				jnz nextStackArg
		}
	}
	__asm
	{
		mov eax, FuncPtrPtr
		call dword ptr[eax]
		ret
	}
}

template <typename TSign, auto** TFuncPtrPtr, int TFuncPtrIndex = 0>
class ThiscallToCdeclAdapter;

template <typename TResult, auto** TFuncPtrPtr, int TFuncPtrIndex, typename... TArgs>
class ThiscallToCdeclAdapter<TResult(TArgs...), TFuncPtrPtr, TFuncPtrIndex> : public ThiscallToCdeclAdapterBase<TResult, TFuncPtrPtr, TFuncPtrIndex, TArgs...>
{
};
