#include "Engine/Event/input_events.h"

namespace shrine::event
{

KeyPressedEvent::KeyPressedEvent(Window& window, uint32_t keycode)
    : IEvent(CATEGORY_KEYBOARD_EVENT)
    , m_window(window), m_keycode(keycode)
{
}

KeyReleasedEvent::KeyReleasedEvent(Window& window, uint32_t keycode)
    : IEvent(CATEGORY_KEYBOARD_EVENT)
    , m_window(window), m_keycode(keycode)
{
}

KeyRepeatedEvent::KeyRepeatedEvent(Window& window, uint32_t keycode)
    : IEvent(CATEGORY_KEYBOARD_EVENT)
    , m_window(window), m_keycode(keycode)
{
}

}; // shrine::event