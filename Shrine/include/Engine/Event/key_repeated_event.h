// I guess, its okay to use #pragma once
#pragma once

#include "Engine/core.h"
#include "Engine/window.h"
#include "Engine/Event/event.h"

namespace shrine::event
{

class SHRINE_API KeyRepeatedEvent : public IEvent
{
private:
    Window& m_Window;
    uint32_t m_Keycode;
    // uint32_t m_Scancode; // not used
    // uint32_t m_Mods;
public:
    KeyRepeatedEvent(Window& window, uint32_t keycode);
    virtual ~KeyRepeatedEvent() = default;

    EVENT_INITIALIZE(Type::KEY_REPEATED);

    inline uint32_t getKeycode() const { return m_Keycode; }
    inline Window& getWindow() { return m_Window; }
};

}; // shrine::event