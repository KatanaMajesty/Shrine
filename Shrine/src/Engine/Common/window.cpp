#include "Engine/Common/window.h"

#include "Engine/Utility/logger.h"
#include "Engine/Utility/keyboard.h"
#include "Engine/Event/input_events.h"
#include "Engine/Event/window_events.h"
#include "Engine/Common/assert.h"

namespace shrine
{
     
WindowAttributes::WindowAttributes(const std::string& title, uint32_t width, u_int32_t height, bool fullscreen, bool vsync)
    : title(title), width(width), height(height), fullscreen(fullscreen), vsync(vsync)
{
}



/* ===================== */
/* WINDOW IMPLEMENTATION */
/* ===================== */
Window::Window(const ref_t<ScopedPointer<event_bus_type>>& eventBus, const WindowAttributes& attributes)
    : m_internalAttrib{.glfwWindow = nullptr, .shrineShouldClose = false}
    , m_attributes(attributes)
    , m_eventBus(eventBus)
{
    if (!glfwInit()) {
        SHR_LOG_CORE(LogLevel::Critical, "Failed to initailize GLFW");
    }    
}

Window::~Window() {
    // close(); <- this calls WindowClosedEvent twice, which should be avoided
    glfwMakeContextCurrent(nullptr);
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
    if (glewInit() != GLEW_OK) {
        SHR_LOG_CORE(LogLevel::Critical, "Failed to initialize GLEW");
    }

    event::WindowOpenedEvent e(*this);
    getEventBus().publish(e);

    if (!e.cancelled) {
        while (!shouldBeClosed()) {
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.12f, 0.6f, 0.12f, 1.0f);

            getRenderer().render();

            glfwSwapBuffers(getGLFWwindow());
            glfwPollEvents();
        }
    }
}

/**
 * @brief Closes a window, destroying current GLFW OpenGL context (will be removed, when window registry is implemented)
 * 
 */
void Window::close() {
    if (!getGLFWwindow()) {
        return;
    }

    event::WindowClosedEvent e(*this);
    getEventBus().publish(e);

    if (e.cancelled) {
        return;
    }
    m_internalAttrib.shrineShouldClose = true;
    glfwMakeContextCurrent(nullptr);
}

/**
 * @brief Sets window title to @param title
 * 
 * @param title - a string, to be used as a window's title
 */
void Window::setTitle(const std::string& title) {
    event::WindowTitleChangedEvent e(*this, title);
    getEventBus().publish(e);

    if (e.cancelled) {
        return;
    }
    m_attributes.title = title;
    glfwSetWindowTitle(getGLFWwindow(), m_attributes.title.c_str());
}

/**
 * @brief Sets window title to @param title
 * 
 * @param title - a string, to be used as a window's title
 */
void Window::setTitle(std::string&& title) {
    event::WindowTitleChangedEvent e(*this, title);
    getEventBus().publish(e);

    if (e.cancelled) {
        return;
    }
    m_attributes.title = std::move(title);
    glfwSetWindowTitle(getGLFWwindow(), m_attributes.title.c_str());
}


/**
 * @brief Asks window to enter a fullscreen mode
 * 
 */
void Window::goFullscreen() {
    if (getAttributes().fullscreen) {
        return;
    }

    event::WindowFullscreenToggledEvent e(*this, true);
    getEventBus().publish(e);

    if (e.cancelled) {
        return;
    }

    internal_window_type* window = getGLFWwindow();
    SHR_ASSERT(window != nullptr);
    internal_monitor_type* monitor = glfwGetPrimaryMonitor();
    const internal_vidmode_type* mode = glfwGetVideoMode(monitor);
    updatePosition();
    glfwSetWindowMonitor(window, monitor, 0, 0, getAttributes().width, getAttributes().height, mode->refreshRate);
}

/**
 * @brief Asks window to enter a windowed mode
 * 
 */
void Window::goWindowed() {
    if (!getAttributes().fullscreen) {
        return;
    }

    event::WindowFullscreenToggledEvent e(*this, false);
    getEventBus().publish(e);

    if (e.cancelled) {
        return;
    }

    internal_window_type* window = getGLFWwindow();
    SHR_ASSERT(window != nullptr);
    int32_t width = getAttributes().width;
    int32_t height = getAttributes().height;
    glfwSetWindowMonitor(window, nullptr, m_internalAttrib.posX, m_internalAttrib.posY, width, height, 0); // refresh rate is ignored, as monitor is nullptr
}

// void Window::goWindowedFullscreen() {
//     // noimpl
// }

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
    switch(action) {
        case GLFW_PRESS: {
            event::KeyPressedEvent e(*context, keycode); 
            context->getEventBus().publish(e);
            break;
        }
        case GLFW_RELEASE: {
            event::KeyReleasedEvent e(*context, keycode); 
            context->getEventBus().publish(e);
            break;
        }
        case GLFW_REPEAT: {
            event::KeyRepeatedEvent e(*context, keycode); 
            context->getEventBus().publish(e);
            break;
        }
    }
}

// Callback is used for GLFW-specific close actions, such as using window's close flag to close it
void Window::windowCloseCallback(internal_window_type* glfwWindow) {
    Window* context = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
    if (!context) {
        return;
    }

    event::WindowClosedEvent e(*context);
    context->getEventBus().publish(e);

    if (e.cancelled) {
        glfwSetWindowShouldClose(context->getGLFWwindow(), false);
        e.getWindow().m_internalAttrib.shrineShouldClose = false;
    }
}

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
void Window::windowSizeCallback(internal_window_type* glfwWindow, int width, int height) {
    Window* context = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
    if (!context) {
        return;
    }

    event::WindowResizedEvent e(*context, context->getAttributes().fullscreen, width, height);
    context->getEventBus().publish(e);
}

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
void Window::windowFramebufferSizeCallback(internal_window_type* glfwWindow, int width, int height) {
    Window* context = static_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
    if (!context) {
        return;
    }
    
    event::WindowFramebufferChangedEvent e(*context, width, height);
    context->getEventBus().publish(e);
}

void Window::updatePosition() {
    glfwGetWindowPos(getGLFWwindow(), &m_internalAttrib.posX, &m_internalAttrib.posY);
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

bool Window::shouldBeClosed() { 
    return m_internalAttrib.shrineShouldClose || glfwWindowShouldClose(getGLFWwindow()); 
}

} // shrine