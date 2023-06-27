#pragma once

#define WIN32_LEAN_AND_MEAN

#include <exception>
#include "CompilerType.h"
#include "CallingConvention/CdeclToBorlandAdapter.h"
#include "CallingConvention/CdeclToThiscallAdapter.h"
#include "CallingConvention/BorlandToCdeclAdapter.h"
#include "CallingConvention/ThiscallToCdeclAdapter.h"

class CompilerHelper final
{
public:
    static void                 Init                ();

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

    static inline CompilerType CompilerType = CompilerType::Unknown;
};
