#include "Engine/Event/input_events.h"

namespace shrine::event
{

KeyPressedEvent::KeyPressedEvent(Window& window, const Keycode keycode)
    : Event(CATEGORY_KEYBOARD_EVENT)
    , m_window(window), m_keycode(keycode)
{
}

KeyReleasedEvent::KeyReleasedEvent(Window& window, const Keycode keycode)
    : Event(CATEGORY_KEYBOARD_EVENT)
    , m_window(window), m_keycode(keycode)
{
}

KeyRepeatedEvent::KeyRepeatedEvent(Window& window, const Keycode keycode)
    : Event(CATEGORY_KEYBOARD_EVENT)
    , m_window(window), m_keycode(keycode)
{
}

}; // shrine::event