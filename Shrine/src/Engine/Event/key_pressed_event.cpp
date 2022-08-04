#include "Engine/Event/key_pressed_event.h"

namespace shrine::event
{

KeyPressedEvent::KeyPressedEvent(uint32_t keycode)
    : m_Keycode(keycode)
{
}

Type KeyPressedEvent::getType() const { return Type::KEY_PRESSED; }

}; // shrine::event