#include "Engine/Common/application.h"

namespace shrine
{

Application::Application()
    : m_logger(createLogger("SHR_LOGGER"))
    , m_eventBus(makeScoped<Application::event_bus_type>())
    , m_window(makeScoped<Application::window_type>(m_eventBus, WindowAttributes{}))
{
}

ref_t<Logger> Application::createLogger(const std::string& identifier) { return Logger::createLogger<Logger>(SHR_LOGGER_CORE, identifier); }

}; // shrine

