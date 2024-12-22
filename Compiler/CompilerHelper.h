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
            return (static_cast<decltype(*TFuncPtrPtr)>(*TFuncPtrPtr))(args...);

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

    template <auto*... TVirFuncTypePtrs>
    static void                 ApplyWrapVTable     (PVOID pObj)
    {
        (..., AssertVirFuncType<TVirFuncTypePtrs>());
        *static_cast<PVOID*>(pObj) = WrapVTable<TVirFuncTypePtrs...>(*static_cast<PVOID*>(pObj));
    }

private:
    struct VirFuncType
    {
        virtual ~VirFuncType() = default;
    };

public:
    struct VirFuncTypeNoChange      final : VirFuncType
    {
    };

    struct VirFuncTypeDestructor    final : VirFuncType
    {
    };

private:
    template <auto* TVirFuncTypePtr>
    static void                 AssertVirFuncType   ()
    {
        static_assert(dynamic_cast<VirFuncTypeNoChange*>(TVirFuncTypePtr) || dynamic_cast<VirFuncTypeDestructor*>(TVirFuncTypePtr));
    }

    template <auto*... TVirFuncTypePtrs>
    static PVOID                WrapVTable          (PVOID pVTable)
    {
        switch (CompilerType)
        {
        case CompilerType::Borland:
            return VTableAdapter<TVirFuncTypePtrs...>::AdaptToBorland(pVTable);

        case CompilerType::Msvc:
            return pVTable;

        default:
            throw std::exception("Unsupported compiler type!");
        }
    }

    template <auto*... TVirFuncTypePtrs>
    class VTableAdapter
    {
    public:
        static PVOID AdaptToBorland         (PVOID pVTable)
        {
            return AdaptThiscallToBorland(pVTable, std::make_index_sequence<sizeof...(TVirFuncTypePtrs)>());
        }

    private:
        template <size_t... TIndexes>
        static PVOID AdaptThiscallToBorland (PVOID pVTable, std::index_sequence<TIndexes...> indexes)
        {
            static PVOID pCopyVTable[sizeof...(TVirFuncTypePtrs)];
            if (pCopyVTable[0] == nullptr)
                memcpy(pCopyVTable, pVTable, sizeof pCopyVTable);

            static PVOID pNewVTable[] = {
                CallingConventionAdapter<pCopyVTable, TIndexes>::AdaptThiscallToBorland(TVirFuncTypePtrs)...
            };
            return pNewVTable;
        }
    };

    template <auto** TFuncPtrPtr, size_t TFuncPtrIndex>
    class CallingConventionAdapter
    {
    public:
        static constexpr PVOID AdaptThiscallToBorland(auto* pVirFuncType)
        {
            if (dynamic_cast<VirFuncTypeNoChange*>  (pVirFuncType))
                return *(TFuncPtrPtr + TFuncPtrIndex);

            if (dynamic_cast<VirFuncTypeDestructor*>(pVirFuncType))
                return reinterpret_cast<PVOID>(ThiscallToBorlandAdapter<void(PVOID, size_t), TFuncPtrPtr, TFuncPtrIndex>::Call);

            throw std::exception("Unsupported virtual function type!");
        }
    };
};
