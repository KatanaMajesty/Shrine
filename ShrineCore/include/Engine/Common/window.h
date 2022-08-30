#ifndef __SHRINE_ENGINE_COMMON_WINDOW_H__
#define __SHRINE_ENGINE_COMMON_WINDOW_H__

#include "Engine/Common/common_definitions.h"
#include "Engine/Graphics/renderer.h"
#include "Engine/Event/event.h"
#include "Engine/Event/event_bus.h"
#include "Engine/Graphics/layer_queue.h"

namespace shrine
{

struct SHRINE_API WindowAttributes
{
    std::string title = "Shrine Window";
    uint32_t width = 1280;
    uint32_t height = 720;
    bool fullscreen = false;
    bool vsync = true;
};

    namespace detail
    {

    struct InternalWindowAttr
    {
        GLFWwindow* glfwWindow;
        bool shrineShouldClose = false;
        bool glInitialized = false;
        int32_t posX = 0;
        int32_t posY = 0;
    };

    } // detail

class SHRINE_API Window
{
public:
    using event_bus_type = event::EventBus;

private:
    detail::InternalWindowAttr m_internal;
    WindowAttributes m_attributes;
    // Renderer m_renderer; // no implementation
    ref_type<event_bus_type> m_eventBus;
    ScopedPointer<LayerQueue> m_layerQueue;

public:
    /**
     * @brief Construct a new Window object
     * 
     * @param eventBus preferred event bus, where this window's events will be published
     * @param attributes an object, that represents window's parameters
     */
    Window(event_bus_type& eventBus, const WindowAttributes& attributes);
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    Window(Window&& other);
    virtual ~Window();

    /**
     * @brief Opens the window, sending cancellable WindowOpenedEvent to every application's eventbus subscriber
     * 
     */
    void open();
    
    /**
     * @brief called in main loop. Updates window contents
     * 
     */
    void update();

    /**
     * @brief Closes the window, sending cancellable WindowClosedEvent to every application's eventbus subscriber
     * 
     */
    void close();
    
    /**
     * @brief Set the Vsync object
     * 
     * @param isVsync 
     */
    void setVsync(bool isVsync);

    /**
     * @brief Get the attributes object, that contains specific information about this Window object
     * 
     * @return WindowAttributes& 
     */
    inline WindowAttributes& getAttributes() { return m_attributes; }
    inline const WindowAttributes& getAttributes() const { return m_attributes; }
    
    /**
     * @brief Get the Event Bus object, that is bound to this window object
     * 
     * @return event_bus_type& 
     */
    inline event_bus_type& getEventBus() { return m_eventBus.get(); }

    inline LayerQueue& getLayerQueue() { return *m_layerQueue.get(); }

    /**
     * @brief Sets window title to @param title
     * 
     * @param title - a string, to be used as a window's title
     */
    void setTitle(const std::string& title);
    void setTitle(std::string&& title);

    /**
     * @brief Asks window to enter a fullscreen mode
     * 
     */
    void goFullscreen();

    /**
     * @brief Asks window to enter a windowed mode
     * 
     */
    void goWindowed();

    /**
     * @brief checks if this window object should be closed
     * 
     */
    bool shouldBeClosed();

private:
    inline GLFWwindow* getGLFWwindow() { return m_internal.glfwWindow; }

    void initializeCallbacks();
    void updateGLFWContext();
    void updateGLEWContext();
}; // Window class

} // shrine

#endif // __SHRINE_ENGINE_COMMON_WINDOW_H__