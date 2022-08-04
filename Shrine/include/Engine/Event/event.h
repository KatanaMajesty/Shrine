#ifndef __SHRINE_ENGINE_EVENTS_EVENT_H__
#define __SHRINE_ENGINE_EVENTS_EVENT_H__

#include <string>

#include "Engine/core.h"

namespace shrine::event
{

enum Type
{
    GENERIC, 
    KEY_PRESSED,
    KEY_RELEASED,
    KEY_REPEATED,
};

// TEMPORARY maybe
#define CATEGORY_KEYBOARD_EVENT BIT(1)
#define CATEGORY_MOUSE_EVENT BIT(2)
#define CATEGORY_WINDOW_EVENT BIT(3)

// TEMPORARY
#define EVENT_INITIALIZE(t) static inline shrine::event::Type eventType() { return t; }

// TODO: Implement Event System
class SHRINE_API IEvent
{    
protected:
    uint16_t m_Categories = 1; // category bitmask
    
protected:
    IEvent(uint16_t categories);
    virtual ~IEvent() = default;

public:
    EVENT_INITIALIZE(Type::GENERIC);
    bool ofCategory(uint16_t category);
};

}; // shrine::event 

#endif // __SHRINE_ENGINE_EVENTS_EVENT_H__