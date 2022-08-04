#ifndef __SHRINE_ENGINE_UTILITY_LOGGER_H__
#define __SHRINE_ENGINE_UTILITY_LOGGER_H__

#include <string>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "Engine/core.h"
#include "Engine/Utility/pointer.h"

#define SHRINE_LEVEL_TRACE 0
#define SHRINE_LEVEL_DEBUG 1
#define SHRINE_LEVEL_INFO 2
#define SHRINE_LEVEL_WARN 3
#define SHRINE_LEVEL_ERROR 4
#define SHRINE_LEVEL_CRITICAL 5
#define SHRINE_LEVEL_OFF 6

namespace shrine
{

enum LogLevel
{
    Trace = SHRINE_LEVEL_TRACE,
    Debug = SHRINE_LEVEL_DEBUG,
    Info = SHRINE_LEVEL_INFO,
    Warn = SHRINE_LEVEL_WARN,
    Error = SHRINE_LEVEL_ERROR,
    Critical = SHRINE_LEVEL_CRITICAL,
    Off = SHRINE_LEVEL_OFF
};

// Logger should be rewritten to use macros in order to avoid unnessecary function calls

/**
 * @brief spdlog wrapper for Shrine
 * Only stdout multithreaded logger is supported now
 */
class SHRINE_API Logger
{
public:
    using pointer = Logger*;

private:
    SharedPointer<spdlog::logger> m_Logger; // spdlog instance
    static pointer m_BoundLogger; // Currently bound logger

public:
    Logger(const std::string& name);
    ~Logger() = default;

    // Get/Set logging level of this logger instance
    void        setLevel(LogLevel level);
    LogLevel    getLevel() const;

    template<typename... Args> void log(LogLevel level, const std::string& message, const Args&... args) { m_Logger->log(toSPDLevel(level), message, args...); }
    template<typename... Args> static void tryLog(Logger::pointer logger, LogLevel level, const std::string& message, const Args&... args) {
        if (logger) {
            logger->log(level, message, args...);
        }
    }
    template<typename... Args> static void tryBoundLog(LogLevel level, const std::string& message, const Args&... args) {
        Logger::pointer logger = Logger::getBoundLogger();
        if (logger) {
            logger->log(level, message, args...);
        }
    }

    static void     bindLogger(Logger& logger);
    static pointer  getBoundLogger();

private:
    spdlog::level::level_enum toSPDLevel(LogLevel level);
};

}; // shrine

#endif // __SHRINE_ENGINE_UTILITY_LOGGER_H__
