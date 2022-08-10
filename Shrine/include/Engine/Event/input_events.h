#pragma once

#include "Engine/Common/common_definitions.h"
#include "Engine/Common/window.h"
#include "Engine/Event/event.h"

namespace shrine::event
{

class SHRINE_API KeyPressedEvent : public IEvent
{
private:
    Window& m_window;
    uint32_t m_keycode;
public:
    KeyPressedEvent(Window& window, uint32_t keycode);
    virtual ~KeyPressedEvent() = default;

    EVENT_INITIALIZE(Type::KEY_PRESSED)

    inline uint32_t getKeycode() const { return m_keycode; }
    inline Window& getWindow() { return m_window; }
};

class SHRINE_API KeyReleasedEvent : public IEvent
{
private:
    Window& m_window;
    uint32_t m_keycode;
public:
    KeyReleasedEvent(Window& window, uint32_t keycode);
    virtual ~KeyReleasedEvent() = default;

    EVENT_INITIALIZE(Type::KEY_RELEASED);

    inline uint32_t getKeycode() const { return m_keycode; }
    inline Window& getWindow() { return m_window; }
};

class SHRINE_API KeyRepeatedEvent : public IEvent
{
private:
    Window& m_window;
    uint32_t m_keycode;
public:
    KeyRepeatedEvent(Window& window, uint32_t keycode);
    virtual ~KeyRepeatedEvent() = default;

    EVENT_INITIALIZE(Type::KEY_REPEATED);

    inline uint32_t getKeycode() const { return m_keycode; }
    inline Window& getWindow() { return m_window; }
};

}; // shrine::event