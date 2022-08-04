#include "Engine/application.h"

#include <iostream>

namespace shrine
{

Application::Application()
    : m_Logger("SHR_APP_LOG"), m_Window({}) // <- window constructor is temporary
{
}

Logger& Application::getLogger() { return m_Logger; }
const Logger& Application::getLogger() const { return m_Logger; }

}; // shrine

