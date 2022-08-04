#include "Engine/Event/key_pressed_event.h"

namespace shrine::event
{

KeyPressedEvent::KeyPressedEvent(Window& window, uint32_t keycode)
    : IEvent(CATEGORY_KEYBOARD_EVENT)
    , m_Window(window), m_Keycode(keycode)
{
}

}; // shrine::event