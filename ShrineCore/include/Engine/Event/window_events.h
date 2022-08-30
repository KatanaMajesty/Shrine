#pragma once

#include "Engine/Common/common_definitions.h"
#include "Engine/Common/window.h"
#include "Engine/Event/event.h"

namespace shrine::event
{

class SHRINE_API WindowFullscreenToggledEvent : public CancellableEvent
{
private:
    Window& m_window;
    bool m_fullscreen;

public:
    WindowFullscreenToggledEvent(Window& window, bool isFullscreen);

    inline Window& getWindow() { return m_window; }
    inline bool isFullscreen() const { return m_fullscreen; }

    virtual std::string toString() const override {
        return "WindowFullscreenToggledEvent";
    }
};



// called before the window is destructed
class SHRINE_API WindowClosedEvent : public CancellableEvent
{
private:
    Window& m_window;

public:
    WindowClosedEvent(Window& window);

    inline Window& getWindow() { return m_window; }

    virtual std::string toString() const override {
        return "WindowClosedEvent";
    }
};



// called before the window is opened
class SHRINE_API WindowOpenedEvent : public CancellableEvent
{
private:
    Window& m_window;

public:
    WindowOpenedEvent(Window& window);

    inline Window& getWindow() { return m_window; }

    virtual std::string toString() const override {
        return "WindowOpenedEvent";
    }
};



/**
 * @brief For windowed mode windows, this sets the size, in screen coordinates of the content area 
 * or content area of the window. 
 * 
 * The window system may impose limits on window size.
 */
class SHRINE_API WindowResizedEvent : public Event // Not cancellable yet
{
private:
    Window& m_window;
    bool m_fullscreen;
    uint16_t m_width;
    uint16_t m_height;

public:
    WindowResizedEvent(Window& window, bool isFullscreen, uint16_t width, uint16_t height);

    inline Window& getWindow() { return m_window; }
    inline bool isFullscreen() const { return m_fullscreen; }
    inline uint16_t getWidth() const { return m_width; }
    inline uint16_t getHeight() const { return m_height; }

    virtual std::string toString() const override {
        return "WindowResizedEvent";
    }
};



class SHRINE_API WindowFramebufferChangedEvent : public Event // Not cancellable yet
{
private:
    Window& m_window;
    uint16_t m_width;
    uint16_t m_height;

public:
    WindowFramebufferChangedEvent(Window& window, uint16_t width, uint16_t height);

    inline Window& getWindow() { return m_window; }
    inline uint16_t getWidth() const { return m_width; }
    inline uint16_t getHeight() const { return m_height; }

    virtual std::string toString() const override {
        return "WindowFramebufferChangedEvent";
    }
};



class SHRINE_API WindowTitleChangedEvent : public CancellableEvent
{
private:
    Window& m_window;
    std::string_view m_title;

public:
    WindowTitleChangedEvent(Window& window, std::string_view title);

    inline Window& getWindow() { return m_window; }
    inline std::string_view getTitle() const { return m_title; }
    
    virtual std::string toString() const override {
        return "WindowTitleChangedEvent";
    }
};

}; // shrine::event