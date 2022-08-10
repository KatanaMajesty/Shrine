#include "Engine/Common/window.h"

#include <functional>

#include "Engine/Utility/logger.h"
#include "Engine/Utility/keyboard.h"
#include "Engine/Event/input_events.h"
#include "Engine/Event/window_events.h"

namespace shrine
{
     
WindowAttributes::WindowAttributes(const std::string& title, uint32_t width, u_int32_t height, bool vsync)
    : title(title), width(width), height(height), vsync(vsync)
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
    // TODO: implement
    // event::Listener::addCallback(event::Type::WINDOW_FULLSCREEN_TOGGLED, WindowListener::onWindowFullscreenToggled);
    // event::Listener::addCallback(event::Type::WINDOW_CLOSED, WindowListener::onWindowClosed);
    // event::Listener::addCallback(event::Type::WINDOW_OPENED, WindowListener::onWindowOpened);
    // event::Listener::addCallback(event::Type::WINDOW_RESIZED, WindowListener::onWindowSizeChanged);
    // event::Listener::addCallback(event::Type::WINDOW_FRAMEBUFFER_RESIZED, WindowListener::onWindowFramebufferChanged);
    // event::Listener::addCallback(event::Type::WINDOW_TITLE_CHANGED, WindowListener::onWindowTitleChanged);
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
    : m_internalAttrib{.glfwWindow = nullptr, .shrineShouldClose = false}
    , m_attributes(attributes)
    , m_eventHandler() // <- Dirty, but should be defined BEFORE WindowListener is created
    , m_eventListener(m_eventHandler.makeListener<WindowListener>())
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

    m_internalAttrib.glfwWindow = glfwCreateWindow(m_attributes.width, m_attributes.height, m_attributes.title.c_str(), nullptr, nullptr);
    if (!getGLFWwindow()) {
        SHR_LOG_CORE(LogLevel::Critical, "Failed to create a GLFW window");
    }

    Window::initializeWindowCallbacks(*this);

    updateGLFWContext();
    // TODO start: Refactor is needed
    if (glewInit() != GLEW_OK) {
        SHR_LOG_CORE(LogLevel::Critical, "Failed to initialize GLEW");
    } // TODO end

    getEventHandler().callEvent<event::WindowOpenedEvent>(*this);

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

    m_eventHandler.callEvent<event::WindowClosedEvent>(*this);

    m_internalAttrib.shrineShouldClose = true;
    // Should be checked
    glfwMakeContextCurrent(nullptr);
}

WindowAttributes& Window::getAttributes() { return m_attributes; }

Window::renderer_type& Window::getRenderer() { return m_renderer; }

Window::event_handler_type& Window::getEventHandler() { return m_eventHandler; }

void Window::setTitle(const std::string& title) {
    m_attributes.title = title;
    getEventHandler().callEvent<event::WindowTitleChangedEvent>(*this, m_attributes.title);
}

void Window::setTitle(std::string&& title) {
    m_attributes.title = std::move(title);
    getEventHandler().callEvent<event::WindowTitleChangedEvent>(*this, m_attributes.title);
}

Window::internal_window_type* Window::getGLFWwindow() { return m_internalAttrib.glfwWindow; }

Window::internal_window_type* Window::getGLFWwindow() const { return m_internalAttrib.glfwWindow; }

void Window::initializeWindowCallbacks(Window& window) {
    Window::internal_window_type* glfwWindow = window.getGLFWwindow();
    glfwSetWindowUserPointer(glfwWindow, &window);
    glfwSetKeyCallback(glfwWindow, Window::keyInputCallback);
    glfwSetWindowCloseCallback(glfwWindow, Window::windowCloseCallback);
    glfwSetWindowSizeCallback(glfwWindow, Window::windowSizeCallback);
    glfwSetFramebufferSizeCallback(glfwWindow, Window::windowFramebufferSizeCallback);
}

void Window::keyInputCallback(internal_window_type* glfwWindow, int keycode, int scancode, int action, int mods) {
    Window* context = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
    if (!context) {
        return;
    }
    switch (action) {
        case GLFW_REPEAT: {context->getEventHandler().callEvent<event::KeyRepeatedEvent>(*context, keycode); break;}
        case GLFW_PRESS: {context->getEventHandler().callEvent<event::KeyPressedEvent>(*context, keycode); break;}
        case GLFW_RELEASE: {context->getEventHandler().callEvent<event::KeyReleasedEvent>(*context, keycode); break;}
    }
}

void Window::windowCloseCallback(internal_window_type* glfwWindow) {
    Window* context = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
    if (!context) {
        return;
    }
    context->getEventHandler().callEvent<event::WindowClosedEvent>(*context);
}

void Window::windowSizeCallback(internal_window_type* glfwWindow, int width, int height) {
    Window* context = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
    if (!context) {
        return;
    }
    context->getEventHandler().callEvent<event::WindowResizedEvent>(*context, (uint16_t)width, (uint16_t)height);
}

void Window::windowFramebufferSizeCallback(internal_window_type* glfwWindow, int width, int height) {
    Window* context = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
    if (!context) {
        return;
    }
    context->getEventHandler().callEvent<event::WindowFramebufferChangedEvent>(*context, (uint16_t)width, (uint16_t)height);
}

void Window::updateGLFWContext() {
    if (!getGLFWwindow()) {
        SHR_LOG_CORE(LogLevel::Error, "Couldn't update GLFW context for a window {}, detatching the context...", m_attributes.title);
    }
    glfwMakeContextCurrent(getGLFWwindow());
}
    
void Window::setVsync(bool enabled) {
     getAttributes().vsync = enabled; 
     glfwSwapInterval(enabled);
}

bool Window::shouldBeClosed() const { 
    return m_internalAttrib.shrineShouldClose || glfwWindowShouldClose(getGLFWwindow()); 
}

} // shrine