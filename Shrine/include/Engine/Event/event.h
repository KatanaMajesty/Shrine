#ifndef __SHRINE_ENGINE_EVENTS_EVENT_H__
#define __SHRINE_ENGINE_EVENTS_EVENT_H__

#include "Engine/Common/common_definitions.h"

namespace shrine::event
{

// TEMPORARY maybe
#define CATEGORY_KEYBOARD_EVENT BIT(1)
#define CATEGORY_MOUSE_EVENT BIT(2)
#define CATEGORY_WINDOW_EVENT BIT(3)

// TODO: Implement Event System
class SHRINE_API Event
{    
protected:
    uint16_t m_categories = 1; // category bitmask
    
protected:
    Event(uint16_t categories);
    virtual ~Event() = default;

public:
    bool ofCategory(uint16_t category);
};



// Event that can be cancelled
class SHRINE_API CancellableEvent : public Event
{
protected:
    CancellableEvent(uint16_t categories);

public:
    bool cancelled = false;
    
};

}; // shrine::event 

#endif // __SHRINE_ENGINE_EVENTS_EVENT_H__