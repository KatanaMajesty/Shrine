#include "Engine/Event/key_released_event.h"

namespace shrine::event
{

KeyReleasedEvent::KeyReleasedEvent(Window& window, uint32_t keycode)
    : IEvent(CATEGORY_KEYBOARD_EVENT)
    , m_Window(window), m_Keycode(keycode)
{
}

}; // shrine::event