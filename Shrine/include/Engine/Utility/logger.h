#ifndef __SHRINE_ENGINE_UTILITY_LOGGER_H__
#define __SHRINE_ENGINE_UTILITY_LOGGER_H__

#include <string_view>
#include <unordered_map>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "Engine/Common/common_definitions.h"
#include "Engine/Utility/pointer.h"

/**
 * Logger class is very complicated for now and should be rewritten from scratch
 * 
 */

#ifdef SHR_DEBUG
    #define SHR_LOG(type, level, fmt, ...) (Logger::logIfFound(type, level, fmt, ##__VA_ARGS__))
    #define SHR_LOG_CORE(level, fmt, ...) (SHR_LOG(SHR_LOGGER_CORE, level, fmt, ##__VA_ARGS__))
#else
    #define SHR_BOUND_LOG(level, fmt, ...)
    #define SHR_LOG_CORE(level, fmt, ...)
#endif

#define SHR_LEVEL_TRACE 0
#define SHR_LEVEL_DEBUG 1
#define SHR_LEVEL_INFO 2
#define SHR_LEVEL_WARN 3
#define SHR_LEVEL_ERROR 4
#define SHR_LEVEL_CRITICAL 5
#define SHR_LEVEL_OFF 6

namespace shrine
{

enum LogLevel
{
    Trace = SHR_LEVEL_TRACE,
    Debug = SHR_LEVEL_DEBUG,
    Info = SHR_LEVEL_INFO,
    Warn = SHR_LEVEL_WARN,
    Error = SHR_LEVEL_ERROR,
    Critical = SHR_LEVEL_CRITICAL,
    Off = SHR_LEVEL_OFF
};

#define SHR_LOGGER_CORE 11
#define SHR_LOGGER_USER 12

/**
 * @brief spdlog wrapper for Shrine
 * Only stdout multithreaded logger is supported now
 */
class SHRINE_API Logger
{
public:
    template<typename... Args> using format_string_t = spdlog::format_string_t<Args...>;
    using pointer_type = SharedPointer<Logger>;
    using logger_id_type = uint8_t;
    using logger_registry_type = std::unordered_map<logger_id_type, pointer_type>;

// Static class members
private:
    template<typename T> struct isLogger : isBaseOf<Logger, T> {};

    static logger_registry_type s_loggerRegistry;
    
// Non-static class members
private:
    SharedPointer<spdlog::logger> m_logger; // spdlog instance
    
public:
    Logger(const std::string& identifier);
    virtual ~Logger() = default;

    // Wont replace the old logger of the same type, if found one
    template<typename T, typename... Args> 
    static enableIf_type<isLogger<T>::value, T&> createLogger(logger_id_type type, Args&&... args) {
        return static_cast<T&>(*s_loggerRegistry.try_emplace(type, makeShared<T>(std::forward<Args>(args)...)).first->second);
    }

    static pointer_type getLogger(logger_id_type type);

    template<typename... Args> 
    static void logIfFound(logger_id_type type, LogLevel level, format_string_t<Args...> message, Args&&... args) {
        pointer_type ptr = getLogger(type);
        if (ptr) {
            ptr->log(level, message, std::forward<Args>(args)...);
        }
    }

// class member-functions
public:
    template<typename... Args> void log(LogLevel level, format_string_t<Args...> message, Args&&... args) {
        m_logger->log(Logger::toSPDLevel(level), message, std::forward<Args>(args)...);
    }

    // Set logging level of this logger instance
    void setLevel(LogLevel level);

    // Get logging level of this logger instance
    LogLevel getLevel() const;

private:
    static spdlog::level::level_enum toSPDLevel(LogLevel level);

    static LogLevel fromSPDLevel(spdlog::level::level_enum level);
};

}; // shrine

#endif // __SHRINE_ENGINE_UTILITY_LOGGER_H__
