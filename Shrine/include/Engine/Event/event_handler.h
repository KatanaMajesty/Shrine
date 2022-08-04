#ifndef __SHRINE_ENGINE_EVENTS_EVENT_HANDLER_H__
#define __SHRINE_ENGINE_EVENTS_EVENT_HANDLER_H__

#include <vector>
#include <memory>

#include "Engine/core.h"
#include "Engine/Utility/pointer.h"
#include "Engine/Event/event.h"
#include "Engine/Event/event_listener.h"

namespace shrine::event
{

// TODO: Implement Event System
// TODO: Make it concurrent
class SHRINE_API Handler
{
public:
    using listener_pointer = shrine::SharedPointer<Listener>;
    using listener_registry = std::vector<listener_pointer>;
private:
    listener_registry m_ListenerRegistry;
public:
    // T - Listener type
    template<typename T> void makeListener() {
        // Add check isListener : true_type / false_type"
        m_ListenerRegistry.push_back(shrine::makeShared<T>());
    }

    // Implement listener drop function, that removes listener from registry
    // void dropListener();

    template<typename E, typename... Args> void callEvent(Args&&... args) {
        // Add check "isEvent : true_type / false_type" 
        E event = E(std::forward<Args>(args)...); // SFINAE for IEvent
        for (const listener_pointer& pointer : m_ListenerRegistry) {
            Listener& listener = *pointer;
            listener.handleCallbacks(E::eventType(), static_cast<IEvent&>(event));
        }
    }
};

}; // shrine::event

#endif // __SHRINE_ENGINE_EVENTS_EVENT_HANDER_H__