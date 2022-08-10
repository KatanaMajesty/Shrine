#pragma once

#include "Engine/Common/common_definitions.h"
#include "Engine/Common/window.h"
#include "Engine/Event/event.h"

namespace shrine::event
{

class WindowFullscreenToggledEvent : public IEvent
{
private:
    Window& m_window;
    bool m_fullscreen;

public:
    WindowFullscreenToggledEvent(Window& window, bool isFullscreen);

    EVENT_INITIALIZE(Type::WINDOW_FULLSCREEN_TOGGLED);

    inline Window& getWindow() { return m_window; }
    inline bool isFullscreen() const { return m_fullscreen; }
};



// called before the window is destructed
// TODO: Make event cancellable, when implemented
class WindowClosedEvent : public IEvent
{
private:
    Window& m_window;

public:
    WindowClosedEvent(Window& window);

    EVENT_INITIALIZE(Type::WINDOW_CLOSED);

    inline Window& getWindow() { return m_window; }
};



// called before the window is opened
// TODO: Make event cancellable, when implemented
class WindowOpenedEvent : public IEvent
{
private:
    Window& m_window;

public:
    WindowOpenedEvent(Window& window);

    EVENT_INITIALIZE(Type::WINDOW_OPENED);

    inline Window& getWindow() { return m_window; }
};



/**
 * @brief For windowed mode windows, this sets the size, in screen coordinates of the content area 
 * or content area of the window. 
 * 
 * The window system may impose limits on window size.
 */
class WindowResizedEvent : public IEvent
{
private:
    Window& m_window;
    uint16_t m_x;
    uint16_t m_y;

public:
    WindowResizedEvent(Window& window, uint16_t x, uint16_t y);

    EVENT_INITIALIZE(Type::WINDOW_RESIZED);

    inline Window& getWindow() { return m_window; }
    inline uint16_t getX() const { return m_x; }
    inline uint16_t getY() const { return m_y; }
};



class WindowFramebufferChangedEvent : public IEvent
{
private:
    Window& m_window;
    uint16_t m_x;
    uint16_t m_y;

public:
    WindowFramebufferChangedEvent(Window& window, uint16_t x, uint16_t y);

    EVENT_INITIALIZE(Type::WINDOW_FRAMEBUFFER_RESIZED);

    inline Window& getWindow() { return m_window; }
    inline uint16_t getX() const { return m_x; }
    inline uint16_t getY() const { return m_y; }
};



class WindowTitleChangedEvent : public IEvent
{
private:
    Window& m_window;
    std::string_view m_title;

public:
    WindowTitleChangedEvent(Window& window, std::string_view title);

    EVENT_INITIALIZE(Type::WINDOW_TITLE_CHANGED);

    inline Window& getWindow() { return m_window; }
    inline std::string_view getTitle() const { return m_title; }
};

}; // shrine::event