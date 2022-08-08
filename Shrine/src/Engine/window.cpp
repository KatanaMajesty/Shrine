#include "Engine/window.h"

#include <functional>

// temp
#include "Engine/Utility/logger.h"
#include "Engine/Utility/keyboard.h"
#include "Engine/Event/key_pressed_event.h"
#include "Engine/Event/key_released_event.h"
#include "Engine/Event/key_repeated_event.h"

namespace shrine
{
     
WindowAttributes::WindowAttributes(const std::string& name, uint32_t width, u_int32_t height, bool vsync)
    : name(name), width(width), height(height), vsync(vsync)
{
}



/* ============================== */
/* WINDOW LISTENER IMPLEMENTATION */
/* ============================== */

WindowListener::WindowListener()
{
    // use Listener's addCallback member-function
    event::Listener::addCallback(event::Type::KEY_PRESSED, WindowListener::onKeyPressed);
    event::Listener::addCallback(event::Type::KEY_RELEASED, WindowListener::onKeyReleased);
    event::Listener::addCallback(event::Type::KEY_REPEATED, WindowListener::onKeyRepeated);
}

bool WindowListener::onKeyPressed(event::IEvent& e) {
    event::KeyPressedEvent& event = static_cast<event::KeyPressedEvent&>(e); // assert this, should be okay
    SHR_LOG_CORE(LogLevel::Debug, "KeyPressedEvent with keyCode: {}", event.getKeycode());
    return false; // shouldn't be handled, just logged
}

bool WindowListener::onKeyReleased(event::IEvent& e) {
    event::KeyReleasedEvent& event = static_cast<event::KeyReleasedEvent&>(e); // assert this, should be okay
    SHR_LOG_CORE(LogLevel::Debug, "KeyReleasedEvent with keyCode: {}", event.getKeycode());
    if (event.getKeycode() == SHR_KEY_ESCAPE) {
        event.getWindow().close();
        return true;
    }
    return false;
}

bool WindowListener::onKeyRepeated(event::IEvent& e) {
    event::KeyRepeatedEvent& event = static_cast<event::KeyRepeatedEvent&>(e); // assert this, should be okay
    SHR_LOG_CORE(LogLevel::Debug, "KeyRepeatedEvent with keyCode: {}", event.getKeycode());
    return false; // shouldn't be handled, just logged
}



/* ===================== */
/* WINDOW IMPLEMENTATION */
/* ===================== */

Window::Window(const WindowAttributes& attributes)
    : m_InternalAttrib{.glfwWindow = nullptr, .shrineShouldClose = false}
    , m_Attributes(attributes)
    , m_EventHandler() // <- Dirty, but should be defined BEFORE WindowListener is created
    , m_EventListener(m_EventHandler.makeListener<WindowListener>())
{
    if (!glfwInit()) {
        SHR_LOG_CORE(LogLevel::Critical, "Failed to initailize GLFW");
    }
}

Window::~Window() {
    close();
    glfwDestroyWindow(getGLFWwindow());

    // GLFW should not be terminated when window registry is implemented
    glfwTerminate(); // TODO: remove temporary solution
}

void Window::open() {
    if (getGLFWwindow()) {
        close();
    }

    m_InternalAttrib.glfwWindow = glfwCreateWindow(m_Attributes.width, m_Attributes.height, m_Attributes.name.c_str(), nullptr, nullptr);
    if (!getGLFWwindow()) {
        SHR_LOG_CORE(LogLevel::Critical, "Failed to create a GLFW window");
    }

    Window::initializeWindowCallbacks(*this);

    updateGLFWContext();
    // TODO start: Refactor is needed
    if (glewInit() != GLEW_OK) {
        SHR_LOG_CORE(LogLevel::Critical, "Failed to initialize GLEW");
    } // TODO end

    while (!shouldBeClosed()) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.12f, 0.6f, 0.12f, 1.0f);
        
        getRenderer().render();

        glfwSwapBuffers(getGLFWwindow());
        glfwPollEvents();
    }
}

void Window::close() {
    if (!getGLFWwindow()) {
        return;
    }

    m_InternalAttrib.shrineShouldClose = true;
    // Should be checked
    glfwMakeContextCurrent(nullptr);
}

WindowAttributes& Window::getAttributes() { return m_Attributes; }

Window::renderer_type& Window::getRenderer() { return m_Renderer; }

Window::event_handler_type& Window::getEventHandler() { return m_EventHandler; }

Window::internal_window_type* Window::getGLFWwindow() { return m_InternalAttrib.glfwWindow; }

Window::internal_window_type* Window::getGLFWwindow() const { return m_InternalAttrib.glfwWindow; }

void Window::initializeWindowCallbacks(Window& window) {
    glfwSetWindowUserPointer(window.getGLFWwindow(), &window);
    glfwSetKeyCallback(window.getGLFWwindow(), Window::keyInputCallback);
}

void Window::keyInputCallback(internal_window_type* glfwWindow, int keycode, int scancode, int action, int mods) {
    Window* context = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
    if (!context) {
        return;
    }
    if (action == GLFW_REPEAT) {
        context->getEventHandler().callEvent<event::KeyRepeatedEvent>(*context, keycode);
    } else if (action == GLFW_PRESS) {
        context->getEventHandler().callEvent<event::KeyPressedEvent>(*context, keycode);
    } else { // assert action is GLFW_RELEASE
        context->getEventHandler().callEvent<event::KeyReleasedEvent>(*context, keycode);
    }
}

void Window::updateGLFWContext() {
    if (!getGLFWwindow()) {
        SHR_LOG_CORE(LogLevel::Error, "Couldn't update GLFW context for a window {}, detatching the context...", m_Attributes.name);
    }
    glfwMakeContextCurrent(getGLFWwindow());
}
    
void Window::setVsync(bool enabled) {
     getAttributes().vsync = enabled; 
     glfwSwapInterval(enabled);
}

bool Window::shouldBeClosed() const { 
    return m_InternalAttrib.shrineShouldClose || glfwWindowShouldClose(getGLFWwindow()); 
}

} // shrine