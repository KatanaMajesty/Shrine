#ifndef __SHRINE_ENGINE_WINDOW__
#define __SHRINE_ENGINE_WINDOW__

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Engine/Common/common_definitions.h"
#include "Engine/Renderer/renderer.h"
#include "Engine/Event/event_handler.h"

namespace shrine
{

struct SHRINE_API WindowAttributes
{
    std::string title;
    uint32_t width;
    uint32_t height;
    bool vsync;

    WindowAttributes(const std::string& title = "Shrine Application", 
                    uint32_t width = 1280, u_int32_t height = 720, bool vsync = true);
};



struct WinInternalAttr
{
    GLFWwindow* glfwWindow;
    bool shrineShouldClose = false;
};



class WindowListener : public event::Listener
{
public:
    WindowListener();

    // input event callbacks
    static bool onKeyPressed(event::IEvent& e);
    static bool onKeyReleased(event::IEvent& e);
    static bool onKeyRepeated(event::IEvent& e);

    // window event callbacks
    // TODO: implement
    // TODO: implement window full screen mode
    // static bool onWindowFullscreenToggled(event::IEvent& e);
    // static bool onWindowClosed(event::IEvent& e);
    // static bool onWindowOpened(event::IEvent& e);
    // static bool onWindowSizeChanged(event::IEvent& e);
    // static bool onWindowFramebufferChanged(event::IEvent& e);
    // static bool onWindowTitleChanged(event::IEvent& e);
}; // WindowListener class



class SHRINE_API Window
{
public:
    using renderer_type = renderer::Renderer;
    using internal_window_type = GLFWwindow;
    using event_handler_type = event::Handler;

private:
    WinInternalAttr m_internalAttrib;
    WindowAttributes m_attributes;
    // This order of handler and listener is important. Should be rewritten to use better architecture
    event_handler_type m_eventHandler;
    ref_t<WindowListener> m_eventListener;
    renderer_type m_renderer; // no implementation

public:
    Window(const WindowAttributes& attributes);
    ~Window();

    void open();
    void close();
    void setVsync(bool isVsync);

    WindowAttributes& getAttributes();
    renderer_type& getRenderer();
    event_handler_type& getEventHandler();

    void setTitle(const std::string& title);
    void setTitle(std::string&& title);
private:
    internal_window_type* getGLFWwindow();
    internal_window_type* getGLFWwindow() const;

    static void initializeWindowCallbacks(Window& window);
    static void keyInputCallback(internal_window_type* glfwWindow, int keycode, int scancode, int action, int mods);
    static void windowCloseCallback(internal_window_type* glfwWindow);
    static void windowSizeCallback(internal_window_type* glfwWindow, int width, int height);
    static void windowFramebufferSizeCallback(internal_window_type* glfwWindow, int width, int height);

    void updateGLFWContext();
    bool shouldBeClosed() const; // will never be used by user, as there is WindowAttributes getter
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