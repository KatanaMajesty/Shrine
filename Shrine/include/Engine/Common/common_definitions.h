#ifndef __SHRINE_ENGINE_CORE_H__
#define __SHRINE_ENGINE_CORE_H__

#if defined(SHR_PLATFORM_UNIX)
    #include <signal.h>

    #define SHRINE_API
    #define SHR_BREAK() raise(SIGTRAP)
#elif defined(SHR_PLATFORM_WIN)
    #if defined(SHR_BUILD_DLL)
        #define SHRINE_API __declspec(dllexport)
    #elif defined(SHR_BUILD_STATIC)
        #define SHRINE_API
        #define SHR_BREAK()   // noimpl
        // #define SHR_BREAK DebugBreak()
    #else
        #define SHRINE_API __declspec(dllimport)
    #endif
#endif

#define BIT(x) (1 << x)

#include <functional>
#include <type_traits>

namespace shrine
{
template<typename T> using ref_t = std::reference_wrapper<T>;
template<bool Expr, class T = void> using enableIf_type = typename std::enable_if<Expr, T>::type;
template<typename B, typename D> using isBaseOf = std::is_base_of<B, D>;
} // shrine

#endif // __SHRINE_ENGINE_CORE_H__