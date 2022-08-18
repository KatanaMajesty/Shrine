#ifndef __SHRINE_ENGINE_WINDOW__
#define __SHRINE_ENGINE_WINDOW__

#include "Engine/Common/common_definitions.h"
#include "Engine/Graphics/renderer.h"
#include "Engine/Event/event.h"
#include "Engine/Event/event_bus.h"

namespace shrine
{

struct SHRINE_API WindowAttributes
{
    std::string title;
    uint32_t width;
    uint32_t height;
    bool fullscreen;
    bool vsync;

    WindowAttributes(const std::string& title = "Shrine Application", 
                    uint32_t width = 1280, u_int32_t height = 720, bool fullscreen = false, bool vsync = true);
};

struct WinInternalAttr
{
    GLFWwindow* glfwWindow;
    bool shrineShouldClose = false;
    int32_t posX; // Window position on screen
    int32_t posY; // Window position on screen
};

class SHRINE_API Window
{
public:
    using renderer_type = Renderer;
    using internal_window_type = GLFWwindow;
    using internal_monitor_type = GLFWmonitor;
    using internal_vidmode_type = GLFWvidmode;
    using event_bus_type = event::EventBus;

private:
    WinInternalAttr m_internalAttrib;
    WindowAttributes m_attributes;
    renderer_type m_renderer; // no implementation
    ref_t<ScopedPointer<event_bus_type>> m_eventBus;

public:
    Window(const ref_t<ScopedPointer<event_bus_type>>& eventBus, const WindowAttributes& attributes);
    ~Window();

    void open();
    void close();
    void setVsync(bool isVsync);

    inline WindowAttributes& getAttributes() { return m_attributes; }
    inline renderer_type& getRenderer() { return m_renderer; }
    inline event_bus_type& getEventBus() { return *m_eventBus.get(); }

    void setTitle(const std::string& title);
    void setTitle(std::string&& title);

    void goFullscreen();
    void goWindowed();
    // no support for this now
    // void goWindowedFullscreen();
private:
    inline internal_window_type* getGLFWwindow() { return m_internalAttrib.glfwWindow; }

    static void initializeWindowCallbacks(Window& window);
    static void keyInputCallback(internal_window_type* glfwWindow, int keycode, int scancode, int action, int mods);
    static void windowCloseCallback(internal_window_type* glfwWindow);
    static void windowSizeCallback(internal_window_type* glfwWindow, int width, int height);
    static void windowFramebufferSizeCallback(internal_window_type* glfwWindow, int width, int height);

    // updates internal attributes posX and posY of a window
    void updatePosition();
    void updateGLFWContext();
    bool shouldBeClosed(); // will never be used by user, as there is WindowAttributes getter
}; // Window class

// TODO: Implement window registry, that will hold all currently opened and bound to Shrine windows
//      It should be responsible for opening, closing and returning window contexts to API/Engine
//      Maybe it should be moved into separate file/class called Registry<T>?
//      Registry should also be concurrent, as every window, probably, will be ran on separate thread
class WindowRegistry
{
    // No implementation
};


} // shrine

#endif // __SHRINE_ENGINE_WINDOW__