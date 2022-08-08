#include "Engine/Utility/logger.h"

namespace shrine
{

Logger::logger_registry_type Logger::s_LoggerRegistry;

Logger::Logger(const std::string& name)
    : m_Logger(spdlog::stdout_color_mt(name)) 
{
    m_Logger->set_pattern("[%n] [%T %l]: %v");
}

Logger::pointer_type Logger::getLogger(Logger::logger_id_type type) {
    Logger::logger_registry_type::const_iterator iter = s_LoggerRegistry.find(type);
    if (iter != s_LoggerRegistry.end()) {
        return iter->second;
    }
    return {nullptr}; // ScopedPointer with nullptr inside
}

void Logger::setLevel(LogLevel level) { spdlog::set_level(Logger::toSPDLevel(level)); }

LogLevel Logger::getLevel() const { return Logger::fromSPDLevel(m_Logger->level()); }

spdlog::level::level_enum Logger::toSPDLevel(LogLevel level) { return static_cast<spdlog::level::level_enum>(level); }

LogLevel Logger::fromSPDLevel(spdlog::level::level_enum level) { return static_cast<LogLevel>(level); }

}; // shrine