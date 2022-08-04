// I guess, its okay to use #pragma once
#pragma once

#include "Engine/core.h"
#include "Engine/Event/event.h"

namespace shrine::event
{

class SHRINE_API KeyPressedEvent : public IEvent
{
private:
    uint32_t m_Keycode;
    // uint32_t m_Scancode; // not used
    // uint32_t m_Mods;
public:
    KeyPressedEvent(uint32_t keycode);
    virtual ~KeyPressedEvent() = default;

    STATIC_EVENT_INITIALIZE(KEY_PRESSED)
    virtual Type getType() const override;

    inline uint32_t getKeycode() const { return m_Keycode; }
};

}; // shrine::event