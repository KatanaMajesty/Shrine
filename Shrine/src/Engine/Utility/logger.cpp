#include "Engine/Utility/logger.h"

namespace shrine
{

Logger::Logger(const std::string& name)
    : m_Logger(spdlog::stdout_color_mt(name)) 
{
    m_Logger->set_pattern("[%n] [%T %l]: %v");
}

void Logger::setLevel(LogLevel level) { spdlog::set_level(static_cast<spdlog::level::level_enum>(level)); }
LogLevel Logger::getLevel() const { return static_cast<LogLevel>(m_Logger->level()); }

// Staticly bound logger
Logger* Logger::m_BoundLogger = nullptr;

void Logger::bindLogger(Logger& logger) { Logger::m_BoundLogger = &logger; }
Logger* Logger::getBoundLogger() { return Logger::m_BoundLogger; }

spdlog::level::level_enum Logger::toSPDLevel(LogLevel level) { return static_cast<spdlog::level::level_enum>(level); }

}; // shrine