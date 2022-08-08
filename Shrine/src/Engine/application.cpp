#include "Engine/application.h"

#include <iostream>

namespace shrine
{

Application::Application()
    : m_Logger(createLogger("SHR_LOGGER")), m_Window({}) // <- window constructor is temporary
{
}

ref_t<Logger> Application::createLogger(const std::string& identifier) { return Logger::createLogger<Logger>(SHR_LOGGER_CORE, identifier); }

}; // shrine

