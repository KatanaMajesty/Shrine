#include "Engine/Utility/logger.h"

namespace shrine
{

Logger::Logger(const std::string& name)
    : m_Logger(spdlog::stdout_color_mt(name)) 
{
    m_Logger->set_pattern("[%n] [%T %l]: %v");
}

void Logger::setLevel(LogLevel level) { spdlog::set_level(Logger::toSPDLevel(level)); }

LogLevel Logger::getLevel() const { return Logger::fromSPDLevel(m_Logger->level()); }

// Staticly bound logger
Logger* Logger::s_BoundLogger = nullptr;

void Logger::bindLogger(Logger& logger) { Logger::s_BoundLogger = &logger; }

Logger* Logger::getBoundLogger() { return Logger::s_BoundLogger; }

spdlog::level::level_enum Logger::toSPDLevel(LogLevel level) { return static_cast<spdlog::level::level_enum>(level); }

LogLevel Logger::fromSPDLevel(spdlog::level::level_enum level) { return static_cast<LogLevel>(level); }


}; // shrine