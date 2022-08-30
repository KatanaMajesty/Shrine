#include "Engine/Event/window_events.h"

namespace shrine::event
{

WindowFullscreenToggledEvent::WindowFullscreenToggledEvent(Window& window, bool isFullscreen)
    : CancellableEvent(CATEGORY_WINDOW_EVENT)
    , m_window(window), m_fullscreen(isFullscreen)
{
}

WindowClosedEvent::WindowClosedEvent(Window& window)
    : CancellableEvent(CATEGORY_WINDOW_EVENT)
    , m_window(window)
{
}

WindowOpenedEvent::WindowOpenedEvent(Window& window)
    : CancellableEvent(CATEGORY_WINDOW_EVENT)
    , m_window(window)
{
}

WindowResizedEvent::WindowResizedEvent(Window& window, bool isFullscreen, uint16_t width, uint16_t height)
    : Event(CATEGORY_WINDOW_EVENT)
    , m_window(window), m_fullscreen(isFullscreen), m_width(width), m_height(height)
{
}

WindowFramebufferChangedEvent::WindowFramebufferChangedEvent(Window& window, uint16_t width, uint16_t height)
    : Event(CATEGORY_WINDOW_EVENT)
    , m_window(window), m_width(width), m_height(height)
{
}

WindowTitleChangedEvent::WindowTitleChangedEvent(Window& window, std::string_view title)
    : CancellableEvent(CATEGORY_WINDOW_EVENT)
    , m_window(window), m_title(title)
{
}

}; // shrine::event