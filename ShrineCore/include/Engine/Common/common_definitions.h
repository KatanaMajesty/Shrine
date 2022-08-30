#ifndef __SHRINE_ENGINE_COMMON_COMMON_DEFINITIONS_H__
#define __SHRINE_ENGINE_COMMON_COMMON_DEFINITIONS_H__


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



// Definitions, that are only in release mode
#if !defined(SHR_DEBUG)
    #define SHR_NASSERT
#endif

#define BIT(x) (1 << x)

// Requires <functional> and <type_traits> headers from STD to work! They are in PCH now
namespace shrine
{
template<typename T> using ref_type = std::reference_wrapper<T>;
template<bool Expr, class T = void> using enableIf_type = typename std::enable_if<Expr, T>::type;
template<typename B, typename D> using isBaseOf = std::is_base_of<B, D>;

template<typename T> using ScopedPointer = std::unique_ptr<T>;
template<typename T> using SharedPointer = std::shared_ptr<T>;
template<typename T> using WeakPointer = std::weak_ptr<T>;

template<typename T, typename... Args> ScopedPointer<T> makeScoped(Args&&... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T, typename... Args> SharedPointer<T> makeShared(Args&&... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

} // shrine



// should be before pointer aliases
#include "Engine/Common/logger.h"

#ifndef SHR_NASSERT
    #define _SHR_ASSERT_IMPL(expr, msg, ...) { if (!(expr)) { SHR_LOG_CORE(LogLevel::Critical, msg, ##__VA_ARGS__); SHR_BREAK(); }}

    #define SHR_ASSERT(expr) _SHR_ASSERT_IMPL(expr, "Assertion {0} failed at {1}:{2}", #expr, std::filesystem::path(__FILE__).filename().c_str(), __LINE__)
#else
    #define SHR_ASSERT(expr, msg, ...)
#endif // !defined(SHR_NASSERT)

#endif // __SHRINE_ENGINE_COMMON_COMMON_DEFINITIONS_H__