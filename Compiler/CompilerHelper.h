#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <exception>
#include "CompilerType.h"
#include "CallingConvention/BorlandToCdeclAdapter.h"
#include "CallingConvention/CdeclToBorlandAdapter.h"
#include "CallingConvention/CdeclToThiscallAdapter.h"
#include "CallingConvention/ThiscallToBorlandAdapter.h"
#include "CallingConvention/ThiscallToCdeclAdapter.h"

class CompilerHelper final
{
public:
    static void                 Init                ();

    static inline CompilerType CompilerType = CompilerType::Unknown;

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
            throw std::exception("Unsupported compiler type");
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
            throw std::exception("Unsupported compiler type");
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
            throw std::exception("Unsupported compiler type");
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
            throw std::exception("Unsupported compiler type");
        }
    }

    template <auto*... TVFuncTypePtrs>
    static void                 ApplyWrapVTable     (PVOID pObj)
    {
        (..., AssertVFuncType<TVFuncTypePtrs>());
        *static_cast<PVOID*>(pObj) = WrapVTable<TVFuncTypePtrs...>(*static_cast<PVOID*>(pObj));
    }

private:
    struct VFuncType
    {
        virtual ~VFuncType() = default;
    };

public:
    struct VFuncTypeNoChange final : VFuncType
    {
    };

    struct VFuncTypeDestructor final : VFuncType
    {
    };

private:
    template <auto* TVFuncTypePtr>
    static void                 AssertVFuncType     ()
    {
        static_assert(
            dynamic_cast<VFuncTypeNoChange*>(TVFuncTypePtr) || dynamic_cast<VFuncTypeDestructor*>(TVFuncTypePtr));
    }

    template <auto*... TVFuncTypePtrs>
    static PVOID                WrapVTable          (PVOID pVTable)
    {
        switch (CompilerType)
        {
        case CompilerType::Borland:
            return VTableAdapter<TVFuncTypePtrs...>::AdaptToBorland(pVTable);

        case CompilerType::Msvc:
            return pVTable;

        default:
            throw std::exception("Unsupported compiler type");
        }
    }

    template <auto*... TVFuncTypePtrs>
    class VTableAdapter
    {
    public:
        static PVOID AdaptToBorland         (PVOID pVTable)
        {
            return AdaptThiscallToBorland(pVTable, std::make_index_sequence<sizeof...(TVFuncTypePtrs)>());
        }

    private:
        template <size_t... TIndexes>
        static PVOID AdaptThiscallToBorland (PVOID pVTable, std::index_sequence<TIndexes...> indexes)
        {
            static PVOID pCopyVTable[sizeof...(TVFuncTypePtrs)];
            if (pCopyVTable[0] == nullptr)
                memcpy(pCopyVTable, pVTable, sizeof pCopyVTable);

            static PVOID pNewVTable[] = {
                CallingConventionAdapter<pCopyVTable, TIndexes>::AdaptThiscallToBorland(TVFuncTypePtrs)...
            };
            return pNewVTable;
        }
    };

    template <auto** TFuncPtrPtr, size_t TFuncPtrIndex>
    class CallingConventionAdapter
    {
    public:
        static constexpr PVOID AdaptThiscallToBorland(auto* pVFuncType)
        {
            if (dynamic_cast<VFuncTypeNoChange*>(pVFuncType))
                return *(TFuncPtrPtr + TFuncPtrIndex);

            if (dynamic_cast<VFuncTypeDestructor*>(pVFuncType))
                return ThiscallToBorlandAdapter<void(PVOID, size_t), TFuncPtrPtr, TFuncPtrIndex>::Call;

            throw std::exception("Unsupported virtual function type");
        }
    };
};
