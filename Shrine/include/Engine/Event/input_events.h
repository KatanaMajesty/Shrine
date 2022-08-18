#pragma once

#include "Engine/Common/common_definitions.h"
#include "Engine/Common/window.h"
#include "Engine/Event/event.h"

namespace shrine::event
{

// Called when key is pressed
class SHRINE_API KeyPressedEvent : public Event
{
private:
    Window& m_window;
    uint32_t m_keycode;
public:
    KeyPressedEvent(Window& window, uint32_t keycode);
    virtual ~KeyPressedEvent() = default;

    inline uint32_t getKeycode() const { return m_keycode; }
    inline Window& getWindow() { return m_window; }
};



// Called when key is released
class SHRINE_API KeyReleasedEvent : public Event
{
private:
    Window& m_window;
    uint32_t m_keycode;
public:
    KeyReleasedEvent(Window& window, uint32_t keycode);
    virtual ~KeyReleasedEvent() = default;

    inline uint32_t getKeycode() const { return m_keycode; }
    inline Window& getWindow() { return m_window; }
};



// Called when key is pressed repeatedly
// Importantly, KeyPressedEvent won't be called simultaneously with this event
class SHRINE_API KeyRepeatedEvent : public Event
{
private:
    Window& m_window;
    uint32_t m_keycode;
public:
    KeyRepeatedEvent(Window& window, uint32_t keycode);
    virtual ~KeyRepeatedEvent() = default;

    inline uint32_t getKeycode() const { return m_keycode; }
    inline Window& getWindow() { return m_window; }
};

}; // shrine::event