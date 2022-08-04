#include "Engine/window.h"

#include <functional>

#include "Engine/Utility/logger.h"
#include "Engine/Event/key_pressed_event.h"
#include "Engine/Event/key_released_event.h"
#include "Engine/Event/key_repeated_event.h"

// TODO: Remove glfw functions from window
// TODO: Abstract OpenGL into renderer context 
namespace shrine
{
     
WindowAttributes::WindowAttributes(const std::string& name, uint32_t width, u_int32_t height, bool vsync)
    : name(name), width(width), height(height), vsync(vsync)
{
}

Window::Window(const WindowAttributes& attributes)
    : m_InternalAttrib{.glfwWindow = nullptr, .shrineShouldClose = false}
    , m_Attributes(attributes)
{
    if (!glfwInit()) {
        Logger::tryBoundLog(LogLevel::Critical, "Failed to initailize GLFW");
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
        Logger::tryBoundLog(LogLevel::Critical, "Failed to create a GLFW window");
    }

    Window::initializeWindowCallbacks(*this);

    updateGLFWContext();
    // TODO start: Refactor is needed
    if (glewInit() != GLEW_OK) {
        Logger::tryBoundLog(LogLevel::Critical, "Failed to initialize GLEW");
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
        Logger::tryBoundLog(LogLevel::Error, "Couldn't update GLFW context for a window {}, detatching the context...", m_Attributes.name);
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