#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <exception>
#include <utility>

#include "CallingConvention/BorlandToCdeclAdapter.h"
#include "CallingConvention/CdeclToBorlandAdapter.h"
#include "CallingConvention/CdeclToThiscallAdapter.h"
#include "CallingConvention/ThiscallToBorlandAdapter.h"
#include "CallingConvention/ThiscallToCdeclAdapter.h"
#include "CompilerType.h"

class CompilerHelper final
{
public:
    static void                 Analyze             ();

    static inline auto CompilerType = CompilerType::Unknown;

    template <typename TResult, auto* TFuncPtr, typename... TArgs>
    static decltype(TFuncPtr)   WrapAsStaticFunc    ()
    {
        static auto* funcPtr = TFuncPtr;
        switch (CompilerType)
        {
        case CompilerType::Borland:
            return reinterpret_cast<decltype(TFuncPtr)>(CdeclToBorlandAdapter<TResult(TArgs...), &funcPtr>::Call);

        case CompilerType::Msvc:
            return TFuncPtr;

        default:
            throw std::exception("Unsupported compiler type!");
        }
    }

    template <typename TResult, auto* TFuncPtr, typename... TArgs>
    static decltype(TFuncPtr)   WrapAsInstanceFunc  ()
    {
        static auto* funcPtr = TFuncPtr;
        switch (CompilerType)
        {
        case CompilerType::Borland:
            return reinterpret_cast<decltype(TFuncPtr)>(CdeclToBorlandAdapter<TResult(TArgs...), &funcPtr>::Call);

        case CompilerType::Msvc:
            return reinterpret_cast<decltype(TFuncPtr)>(CdeclToThiscallAdapter<TResult(TArgs...), &funcPtr>::Call);

        default:
            throw std::exception("Unsupported compiler type!");
        }
    }

    template <typename TResult, auto** TFuncPtrPtr, typename... TArgs>
    static TResult              CallStaticFunc      (TArgs... args)
    {
        switch (CompilerType)
        {
        case CompilerType::Borland:
            return BorlandToCdeclAdapter<TResult(TArgs...), TFuncPtrPtr>::Call(args...);

        case CompilerType::Msvc:
            return (*TFuncPtrPtr)(args...);

        default:
            throw std::exception("Unsupported compiler type!");
        }
    }

    template <typename TResult, auto** TFuncPtrPtr, typename... TArgs>
    static TResult              CallInstanceFunc    (TArgs... args)
    {
        switch (CompilerType)
        {
        case CompilerType::Borland:
            return BorlandToCdeclAdapter<TResult(TArgs...), TFuncPtrPtr>::Call(args...);

        case CompilerType::Msvc:
            return ThiscallToCdeclAdapter<TResult(TArgs...), TFuncPtrPtr>::Call(args...);

        default:
            throw std::exception("Unsupported compiler type!");
        }
    }

    enum class VType
    {
        Member,
        Destructor
    };

    template <VType... VTypes, typename T>
    static T*                   ApplyWrapVTable     (T* pObj)
    {
        *reinterpret_cast<PVOID*>(pObj) = WrapVTable<T, VTypes...>(*reinterpret_cast<PVOID*>(pObj));
        return pObj;
    }

private:
    template <typename T, VType... VTypes>
    static PVOID                WrapVTable          (PVOID pVTable)
    {
        switch (CompilerType)
        {
        case CompilerType::Borland:
            return VTableAdapter<T, VTypes...>::AdaptThiscallToBorland(pVTable);

        case CompilerType::Msvc:
            return pVTable;

        default:
            throw std::exception("Unsupported compiler type!");
        }
    }

    template <typename, VType... VTypes>
    class VTableAdapter
    {
    public:
        static PVOID AdaptThiscallToBorland(PVOID pVTable)
        {
            return AdaptThiscallToBorland(pVTable, std::make_index_sequence<sizeof...(VTypes)>());
        }

    private:
        template <size_t... VIndexes>
        static PVOID AdaptThiscallToBorland(PVOID pVTable, std::index_sequence<VIndexes...>)
        {
            static PVOID pCopyVTable[sizeof...(VTypes)];
            if (pCopyVTable[0] == nullptr)
                memcpy(pCopyVTable, pVTable, sizeof(pCopyVTable));

            static PVOID pNewVTable[] =
            {
                CallingAdapter<pCopyVTable, VIndexes, VTypes>::AdaptThiscallToBorland()...
            };
            return pNewVTable;
        }
    };

    template <PVOID* PPVTable, size_t VIndex, VType VType>
    class CallingAdapter
    {
    public:
        static constexpr PVOID AdaptThiscallToBorland()
        {
            if constexpr (VType == VType::Member)
                return *(PPVTable + VIndex);

            if constexpr (VType == VType::Destructor)
                return reinterpret_cast<PVOID>(ThiscallToBorlandAdapter<void(PVOID, size_t), PPVTable, VIndex>::Call);

            throw std::exception("Unsupported virtual function type!");
        }
    };
};
