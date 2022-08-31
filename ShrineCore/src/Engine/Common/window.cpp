#include "Engine/Common/window.h"

#include "Engine/Common/logger.h"
#include "Engine/Common/common_definitions.h"
#include "Engine/Utility/keyboard.h"
#include "Engine/Event/input_events.h"
#include "Engine/Event/window_events.h"

namespace shrine
{

/* ===================== */
/* WINDOW IMPLEMENTATION */
/* ===================== */

Window::Window(event_bus_type& eventBus, const WindowAttributes& attributes)
    : m_internal{.glfwWindow = nullptr}
    , m_attributes(attributes)
    , m_eventBus(eventBus)
    , m_layerQueue(makeScoped<LayerQueue>())
{    
}



Window::Window(Window&& other)
    : m_internal(std::move(other.m_internal))
    , m_attributes(std::move(other.m_attributes))
    , m_eventBus(other.m_eventBus) 
    , m_layerQueue(std::move(other.m_layerQueue))
{
    other.m_internal.glfwWindow = nullptr;
}



Window::~Window() {
    GLFWwindow* context = getGLFWwindow();
    SHR_LOG_CORE_DEBUG("Window \"{}\" destructor!", getAttributes().title);
    glfwDestroyWindow(context);
}



void Window::open() {
    if (getGLFWwindow()) {
        close();
    }

    m_internal.glfwWindow = glfwCreateWindow(
        getAttributes().width, 
        getAttributes().height, 
        getAttributes().title.c_str(), 
        getAttributes().fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);

    if (!getGLFWwindow()) {
        SHR_LOG_CORE_CRITICAL("Failed to create a window with title \"{}\"", getAttributes().title);
    }

    initializeCallbacks();
    updateGLFWContext();
    updateGLEWContext();
    
    if (!m_internal.glInitialized) {
        SHR_LOG_CORE_CRITICAL("OpenGL context wasn't initialized. The window won't be opened");
        return;
    }

    event::WindowOpenedEvent e(*this);
    getEventBus().publish(e);

    if (e.cancelled) {
        m_internal.shrineShouldClose = true;
    }
}



void Window::update() {
    updateGLFWContext();

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.12f, 0.6f, 0.12f, 1.0f);

    for (auto& ptr : *m_layerQueue) {
        ptr->update();
    }
    // getRenderer().render();

    glfwSwapBuffers(getGLFWwindow());
    glfwPollEvents();
}



void Window::close() {
    GLFWwindow* context = getGLFWwindow();
    if (!context) {
        return;
    }

    event::WindowClosedEvent e(*this);
    getEventBus().publish(e);

    if (e.cancelled) {
        return;
    }
    m_internal.shrineShouldClose = true;
    // glfwDestroyWindow(context);
}



void Window::setVsync(bool enabled) {
    getAttributes().vsync = enabled; 
    glfwSwapInterval(enabled);
}



void Window::setTitle(const std::string& title) {
    event::WindowTitleChangedEvent e(*this, title);
    getEventBus().publish(e);

    if (e.cancelled) {
        return;
    }
    m_attributes.title = title;
    glfwSetWindowTitle(getGLFWwindow(), m_attributes.title.c_str());
}



void Window::setTitle(std::string&& title) {
    event::WindowTitleChangedEvent e(*this, title);
    getEventBus().publish(e);

    if (e.cancelled) {
        return;
    }
    m_attributes.title = std::move(title);
    glfwSetWindowTitle(getGLFWwindow(), m_attributes.title.c_str());
}



void Window::goFullscreen() {
    event::WindowFullscreenToggledEvent e(*this, true);
    getEventBus().publish(e);

    if (e.cancelled) {
        return;
    }

    GLFWwindow* window = getGLFWwindow();
    SHR_ASSERT(window != nullptr);
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    glfwGetWindowPos(getGLFWwindow(), &m_internal.posX, &m_internal.posY);
    glfwSetWindowMonitor(window, monitor, 0, 0, getAttributes().width, getAttributes().height, mode->refreshRate);
}



void Window::goWindowed() {
    event::WindowFullscreenToggledEvent e(*this, false);
    getEventBus().publish(e);

    if (e.cancelled) {
        return;
    }

    GLFWwindow* window = getGLFWwindow();
    SHR_ASSERT(window != nullptr);
    int32_t width = getAttributes().width;
    int32_t height = getAttributes().height;
    // refresh rate is ignored, as monitor is nullptr
    glfwSetWindowMonitor(window, nullptr, m_internal.posX, m_internal.posY, width, height, 0);
}



bool Window::shouldBeClosed() { 
    return m_internal.shrineShouldClose || glfwWindowShouldClose(getGLFWwindow()); 
}



void Window::initializeCallbacks() {
    GLFWwindow* glfwWindow = getGLFWwindow();
    glfwSetWindowUserPointer(glfwWindow, this);

    glfwSetKeyCallback(glfwWindow, [](GLFWwindow* context, int keycode, int scancode, int action, int mods) -> void {
        Window* window = static_cast<Window*>(glfwGetWindowUserPointer(context));
        if (!window) {
            return;
        }
        switch(action) {
            case GLFW_PRESS: {
                event::KeyPressedEvent e(*window, static_cast<Keycode>(keycode)); 
                window->getEventBus().publish(e);
                break;
            }
            case GLFW_RELEASE: {
                event::KeyReleasedEvent e(*window, static_cast<Keycode>(keycode)); 
                window->getEventBus().publish(e);
                break;
            }
            case GLFW_REPEAT: {
                event::KeyRepeatedEvent e(*window, static_cast<Keycode>(keycode)); 
                window->getEventBus().publish(e);
                break;
            }
        }
    });

    // Callback is used for GLFW-specific close actions, such as using window's close flag to close it
    glfwSetWindowCloseCallback(glfwWindow, [](GLFWwindow* context) -> void {
        Window* window = static_cast<Window*>(glfwGetWindowUserPointer(context));
        if (!window) {
            return;
        }

        event::WindowClosedEvent e(*window);
        window->getEventBus().publish(e);

        if (e.cancelled) {
            glfwSetWindowShouldClose(window->getGLFWwindow(), false);
            e.getWindow().m_internal.shrineShouldClose = false;
            return;
        }

        e.getWindow().m_internal.shrineShouldClose = true;
    });

    /**
     * @brief The size of a window can be changed with glfwSetWindowSize. 
     * For windowed mode windows, this sets the size, in screen coordinates 
     * of the content area or content area of the window. The window system 
     * may impose limits on window size.
     * 
     * For full screen windows, the specified size becomes the new resolution 
     * of the window's desired video mode. The video mode most closely matching 
     * the new desired video mode is set immediately. The window is resized to 
     * fit the resolution of the set video mode.
     * 
     * Important note! Do not pass the window size to glViewport or other pixel-based OpenGL calls. 
     * The window size is in screen coordinates, not pixels. Use the framebuffer size, which is in 
     * pixels, for pixel-based calls.
     * 
     * @param glfwWindow 
     * @param width 
     * @param height 
     */
    glfwSetWindowSizeCallback(glfwWindow, [](GLFWwindow* context, int width, int height) -> void {
        Window* window = static_cast<Window*>(glfwGetWindowUserPointer(context));
        if (!window) {
            return;
        }

        event::WindowResizedEvent e(*window, window->getAttributes().fullscreen, width, height);
        window->getEventBus().publish(e);
    });

    /**
     * @brief While the size of a window is measured in screen coordinates, OpenGL works with pixels. 
     * The size you pass into glViewport, for example, should be in pixels. On some machines screen 
     * coordinates and pixels are the same, but on others they will not be. There is a second set of 
     * functions to retrieve the size, in pixels, of the framebuffer of a window.
     * 
     * @param glfwWindow 
     * @param width 
     * @param height 
     */
    glfwSetFramebufferSizeCallback(glfwWindow, [](GLFWwindow* context, int width, int height) -> void {
        Window* window = static_cast<Window*>(glfwGetWindowUserPointer(context));
        if (!window) {
            return;
        }
        
        event::WindowFramebufferChangedEvent e(*window, width, height);
        window->getEventBus().publish(e);
    });
}



void Window::updateGLFWContext() {    
    glfwMakeContextCurrent(getGLFWwindow());
}



void Window::updateGLEWContext() {
    if (glewInit() != GLEW_OK) {
        SHR_LOG_CORE_CRITICAL("Failed to initialize GLEW");
        m_internal.glInitialized = false;
        return;
    }
    m_internal.glInitialized = true;
}

} // shrine