#include "Engine/Event/window_events.h"

namespace shrine::event
{

WindowFullscreenToggledEvent::WindowFullscreenToggledEvent(Window& window, bool isFullscreen)
    : IEvent(CATEGORY_WINDOW_EVENT)
    , m_window(window), m_fullscreen(isFullscreen)
{
}

WindowClosedEvent::WindowClosedEvent(Window& window)
    : IEvent(CATEGORY_WINDOW_EVENT)
    , m_window(window)
{
}

WindowOpenedEvent::WindowOpenedEvent(Window& window)
    : IEvent(CATEGORY_WINDOW_EVENT)
    , m_window(window)
{
}

WindowResizedEvent::WindowResizedEvent(Window& window, uint16_t x, uint16_t y)
    : IEvent(CATEGORY_WINDOW_EVENT)
    , m_window(window), m_x(x), m_y(y)
{
}

WindowFramebufferChangedEvent::WindowFramebufferChangedEvent(Window& window, uint16_t x, uint16_t y)
    : IEvent(CATEGORY_WINDOW_EVENT)
    , m_window(window), m_x(x), m_y(y)
{
}

WindowTitleChangedEvent::WindowTitleChangedEvent(Window& window, std::string_view title)
    : IEvent(CATEGORY_WINDOW_EVENT)
    , m_window(window), m_title(title)
{
}

}; // shrine::event