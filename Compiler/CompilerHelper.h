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

private:
    struct VFuncType{};

public:
    struct VFuncTypeMember      final : VFuncType{};
    struct VFuncTypeDestructor  final : VFuncType{};

    template <auto*... TVFuncTypePtrs>
        requires(std::conjunction_v<std::disjunction<
            std::is_same<decltype(TVFuncTypePtrs), VFuncTypeMember*>,
            std::is_same<decltype(TVFuncTypePtrs), VFuncTypeDestructor*>>...>)
    static void                 ApplyWrapVTable     (PVOID pObj)
    {
        *static_cast<PVOID*>(pObj) = WrapVTable<TVFuncTypePtrs...>(*static_cast<PVOID*>(pObj));
    }

private:
    template <auto*... TVFuncTypePtrs>
    static PVOID                WrapVTable          (PVOID pVTable)
    {
        switch (CompilerType)
        {
        case CompilerType::Borland:
            return VTableAdapter<TVFuncTypePtrs...>::AdaptThiscallToBorland(pVTable);

        case CompilerType::Msvc:
            return pVTable;

        default:
            throw std::exception("Unsupported compiler type!");
        }
    }

    template <auto*... TVFuncTypePtrs>
    class VTableAdapter
    {
    public:
        static PVOID AdaptThiscallToBorland(PVOID pVTable)
        {
            return AdaptThiscallToBorland(pVTable, std::make_index_sequence<sizeof...(TVFuncTypePtrs)>());
        }

    private:
        template <size_t... TVFuncIndexes>
        static PVOID AdaptThiscallToBorland(PVOID pVTable, std::index_sequence<TVFuncIndexes...>)
        {
            static PVOID pCopyVTable[sizeof...(TVFuncTypePtrs)];
            if (pCopyVTable[0] == nullptr)
                memcpy(pCopyVTable, pVTable, sizeof(pCopyVTable));

            static PVOID pNewVTable[] =
            {
                CallingAdapter<pCopyVTable, TVFuncIndexes, decltype(TVFuncTypePtrs)>::AdaptThiscallToBorland()...
            };
            return pNewVTable;
        }
    };

    template <auto** TVTable, size_t TVFuncIndex, typename TVFuncType>
    class CallingAdapter
    {
    public:
        static constexpr PVOID AdaptThiscallToBorland()
        {
            if constexpr (std::is_same_v<TVFuncType, VFuncTypeMember*>)
                return *(TVTable + TVFuncIndex);

            if constexpr (std::is_same_v<TVFuncType, VFuncTypeDestructor*>)
                return reinterpret_cast<PVOID>(ThiscallToBorlandAdapter<void(PVOID, size_t), TVTable, TVFuncIndex>::Call);

            throw std::exception("Unsupported virtual function type!");
        }
    };
};
