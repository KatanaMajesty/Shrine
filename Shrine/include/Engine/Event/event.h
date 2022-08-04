#ifndef __SHRINE_ENGINE_EVENTS_EVENT_H__
#define __SHRINE_ENGINE_EVENTS_EVENT_H__

#include <string>

#include "Engine/core.h"

namespace shrine::event
{

enum Type
{
    GENERIC, 
    KEY_PRESSED
};

// TEMPORARY
#define BIT(x) (1 << x)

// TEMPORARY maybe
#define CATEGORY_KEYBOARD_EVENT BIT(1)
#define CATEGORY_MOUSE_EVENT BIT(2)
#define CATEGORY_WINDOW_EVENT BIT(3)

// TEMPORARY
#define STATIC_EVENT_INITIALIZE(x) static inline Type type() { return Type::x; }

// TODO: Implement Event System
class SHRINE_API IEvent
{    
protected:
    IEvent() = default;
    virtual ~IEvent() = default;

public:
    STATIC_EVENT_INITIALIZE(GENERIC)
    virtual Type getType() const = 0;
};

}; // shrine::event 

#endif // __SHRINE_ENGINE_EVENTS_EVENT_H__