#ifndef __SHRINE_ENGINE_COMMON_LOGGER_H__
#define __SHRINE_ENGINE_COMMON_LOGGER_H__

#include "Engine/Common/common_definitions.h"

#ifdef SHR_DEBUG
    #define SHR_CREATE_LOGGER(name, level, ...) (shrine::Logger::create<shrine::Logger::factory_type>(name, level, ##__VA_ARGS__))
    #define SHR_LOG(name, level, fmt, ...) (shrine::Logger::log(name, level, fmt, ##__VA_ARGS__))
    #define SHR_LOG_CORE(level, fmt, ...) (SHR_LOG("ENGINE_LOGGER", level, fmt, ##__VA_ARGS__))
    #define SHR_LOG_CORE_TRACE(fmt, ...) (SHR_LOG_CORE(shrine::LogLevel::Trace, fmt, ##__VA_ARGS__))
    #define SHR_LOG_CORE_DEBUG(fmt, ...) (SHR_LOG_CORE(shrine::LogLevel::Debug, fmt, ##__VA_ARGS__))
    #define SHR_LOG_CORE_INFO(fmt, ...) (SHR_LOG_CORE(shrine::LogLevel::Info, fmt, ##__VA_ARGS__))
    #define SHR_LOG_CORE_WARN(fmt, ...) (SHR_LOG_CORE(shrine::LogLevel::Warn, fmt, ##__VA_ARGS__))
    #define SHR_LOG_CORE_ERROR(fmt, ...) (SHR_LOG_CORE(shrine::LogLevel::Error, fmt, ##__VA_ARGS__))
    #define SHR_LOG_CORE_CRITICAL(fmt, ...) (SHR_LOG_CORE(shrine::LogLevel::Critical, fmt, ##__VA_ARGS__))
#else
    #define SHR_CREATE_LOGGER(name, level, ...)
    #define SHR_LOG(name, level, fmt, ...)
    #define SHR_LOG_CORE(level, fmt, ...)
    #define SHR_LOG_CORE_TRACE(fmt, ...)
    #define SHR_LOG_CORE_DEBUG(fmt, ...)
    #define SHR_LOG_CORE_INFO(fmt, ...)
    #define SHR_LOG_CORE_WARN(fmt, ...)
    #define SHR_LOG_CORE_ERROR(fmt, ...)
    #define SHR_LOG_CORE_CRITICAL(fmt, ...)
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

/**
 * @brief spdlog wrapper for Shrine
 * Only stdout multithreaded logger is supported now
 */
class Logger
{
public:
    using factory_type = spdlog::synchronous_factory;
    template<typename... Args> using format_string_t = spdlog::format_string_t<Args...>;

private:
    static bool s_initialized;
    static std::string s_pattern;

public:
    inline static void initialize() {
        spdlog::set_pattern(s_pattern);
        s_initialized = true;
    }

    template<typename Factory = factory_type>
    static void create(const std::string& name, LogLevel level, const std::string& pattern = s_pattern, spdlog::color_mode mode = spdlog::color_mode::automatic) {
        if (!s_initialized) {
            throw std::runtime_error("Loggers aren't initialized! Should never happen!");
        }
        SharedPointer<spdlog::logger> logger = Factory::template create<spdlog::sinks::stdout_color_sink_mt>(name, mode);
        logger->set_pattern(pattern);
        logger->set_level(static_cast<spdlog::level::level_enum>(level));
    }

    template<typename... Args>
    static void log(const std::string& name, LogLevel level, format_string_t<Args...> message, Args&&... args) {
        SharedPointer<spdlog::logger> logger = Logger::get(name);
        if (logger) {
            logger->log(static_cast<spdlog::level::level_enum>(level), message, std::forward<Args>(args)...);
        }
    }

    template<typename... Args>
    static void trace(const std::string& name, format_string_t<Args...> message, Args&&... args) {
        Logger::log(name, LogLevel::Trace, message, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static void debug(const std::string& name, format_string_t<Args...> message, Args&&... args) {
        Logger::log(name, LogLevel::Debug, message, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static void info(const std::string& name, format_string_t<Args...> message, Args&&... args) {
        Logger::log(name, LogLevel::Info, message, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static void warn(const std::string& name, format_string_t<Args...> message, Args&&... args) {
        Logger::log(name, LogLevel::Warn, message, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static void error(const std::string& name, format_string_t<Args...> message, Args&&... args) {
        Logger::log(name, LogLevel::Error, message, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static void critical(const std::string& name, format_string_t<Args...> message, Args&&... args) {
        Logger::log(name, LogLevel::Critical, message, std::forward<Args>(args)...);
    }

    inline static const std::string& getDefaultPattern() {
        if (!s_initialized) {
            throw std::runtime_error("Loggers aren't initialized! Should never happen!");
        }
        return s_pattern;
    }

private:
    inline static SharedPointer<spdlog::logger> get(const std::string& name) {
        return spdlog::get(name);
    }
};

}; // shrine

#endif // __SHRINE_ENGINE_COMMON_LOGGER_H__
