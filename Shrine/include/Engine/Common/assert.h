#ifndef __SHRINE_ENGINE_COMMON_ASSERT_H__
#define __SHRINE_ENGINE_COMMON_ASSERT_H__

#include "Engine/Common/common_definitions.h"
#include "Engine/Utility/logger.h"
#include <filesystem>

#ifndef SHR_NASSERT
    #define _SHR_ASSERT_IMPL(expr, msg, ...) { if (!(expr)) {SHR_LOG_CORE(LogLevel::Critical, msg, ##__VA_ARGS__); SHR_BREAK(); }}

    #define SHR_ASSERT(expr) _SHR_ASSERT_IMPL(expr, "Assertion {0} failed at {1}:{2}", #expr, std::filesystem::path(__FILE__).filename().c_str(), __LINE__)
#else
    #define SHR_ASSERT(expr, msg, ...)
#endif // !defined(SHR_NASSERT)

#endif // __SHRINE_ENGINE_COMMON_ASSERT_H__