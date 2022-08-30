#include "Engine/Common/application.h"

namespace shrine
{

Application::Application(const ApplicationAttributes& attributes)
    : m_attributes(attributes)
    , m_eventBus(makeScoped<Application::event_bus_type>())
    , m_window(nullptr)
{    
    if (!glfwInit()) {
        m_glfwInitialized = false;
        SHR_LOG_CORE_CRITICAL("Failed to initailize GLFW");
        return;
    }
    m_glfwInitialized = true;

    // avoid unnecessary allocation
    m_window = makeScoped<Window>(getEventBus(), WindowAttributes{.title = "3D Window Title"});
}

Application::~Application() {
    SHR_LOG_CORE_DEBUG("Application \"{}\" is being terminated!", getAttributes().name);
    if (m_glfwInitialized) {
        glfwTerminate();
    }
}

void Application::run() {
    m_window->open();
    while (!m_window->shouldBeClosed()) { 
        m_window->update();
    }
    m_window.release();
}

}; // shrine

