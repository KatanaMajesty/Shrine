#include "Engine/Event/key_repeated_event.h"

namespace shrine::event
{

KeyRepeatedEvent::KeyRepeatedEvent(Window& window, uint32_t keycode)
    : IEvent(CATEGORY_KEYBOARD_EVENT)
    , m_Window(window), m_Keycode(keycode)
{
}

}; // shrine::event