#ifndef __SHRINE_ENGINE_EVENT_EVENT_LISTENER_H__
#define __SHRINE_ENGINE_EVENT_EVENT_LISTENER_H__

#include <unordered_map>
#include <string>
#include <functional>

#include "Engine/core.h"
#include "Engine/Event/event.h"

namespace shrine::event
{

class SHRINE_API Listener
{
public:
    using event_type = Type;
    using callback_type = std::function<bool(IEvent&)>;
    using event_callbacks = std::unordered_map<event_type, callback_type>;

private:
    event_callbacks m_Callbacks;

public:
    Listener() = default;
    virtual ~Listener() = default;

    // For now, listener only supports one callback for one event_type at a time
    virtual void addCallback(event_type type, callback_type callback);
    // Returns true if all the event callbacks were handled correctly, otherwise false
    virtual bool handleCallbacks(event_type type, IEvent& event) const;
};

}; // shrine::event

#endif // __SHRINE_ENGINE_EVENT_EVENT_LISTENER_H__