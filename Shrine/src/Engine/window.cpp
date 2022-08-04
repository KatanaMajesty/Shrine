#include "Engine/window.h"

#include "Engine/Event/key_pressed_event.h"

#include <iostream>

// TODO: Remove glfw functions from window
// TODO: Abstract OpenGL into renderer context 

namespace shrine
{
     
WindowAttributes::WindowAttributes(const std::string& name, uint32_t width, u_int32_t height)
    : name(name), width(width), height(height)
{
}

Window::Window(const WindowAttributes& attributes)
    : m_Window(nullptr), m_Attributes(attributes)
{
    if (!glfwInit()) {
        Logger::tryBoundLog(LogLevel::Critical, "Failed to initailize GLFW");
    }
}

Window::~Window() {
    close();

    // GLFW should not be terminated when window registry is implemented
    glfwTerminate(); // TODO: remove temporary solution
}

        // VERY TEMPORARY! Should be removed ASAP, was used for testing
        // VERY TEMPORARY! Should be removed ASAP, was used for testing
        // VERY TEMPORARY! Should be removed ASAP, was used for testing
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS) {
        Window& w = *(Window*)glfwGetWindowUserPointer(window);
        w.m_EventHandler.callEvent<event::KeyPressedEvent>(key); // call event
    }
}

void Window::open() {
    if (m_Window) {
        close();
    }

    m_Window = glfwCreateWindow(m_Attributes.width, m_Attributes.height, m_Attributes.name.c_str(), nullptr, nullptr);
    if (!m_Window) {
        Logger::tryBoundLog(LogLevel::Critical, "Failed to create a GLFW window");
    }

    // VERY TEMPORARY! Should be removed ASAP, was used for testing
    // VERY TEMPORARY! Should be removed ASAP, was used for testing
    // VERY TEMPORARY! Should be removed ASAP, was used for testing
    glfwSetWindowUserPointer(m_Window, this);
    glfwSetKeyCallback(m_Window, key_callback);

    updateGLFWContext();
    // TODO start: Refactor is needed
    if (glewInit() != GLEW_OK) {
        Logger::tryBoundLog(LogLevel::Critical, "Failed to initialize GLEW");
    } // TODO end
    updateVsync(isVsync);

    while (!shouldBeClosed()) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.12f, 0.6f, 0.12f, 1.0f);
        
        getRenderer().render();

        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }
}

void Window::close() {
    if (!m_Window) {
        return;
    }
    // Should be checked
    glfwSetWindowShouldClose(m_Window, true);
    glfwDestroyWindow(m_Window);
    glfwMakeContextCurrent(nullptr);
}

renderer::Renderer& Window::getRenderer() { return m_Renderer; }

const renderer::Renderer& Window::getRenderer() const { return m_Renderer; }

void Window::updateGLFWContext() {
    if (!m_Window) {
        Logger::tryBoundLog(LogLevel::Error, "Couldn't update GLFW context for a window {}, detatching the context...", m_Attributes.name);
    }
    glfwMakeContextCurrent(m_Window);
}
    
void Window::updateVsync(bool isVsync) { glfwSwapInterval(isVsync); }

bool Window::shouldBeClosed() const { return glfwWindowShouldClose(m_Window); }

} // shrine