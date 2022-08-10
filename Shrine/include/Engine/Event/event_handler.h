#ifndef __SHRINE_ENGINE_EVENTS_EVENT_HANDLER_H__
#define __SHRINE_ENGINE_EVENTS_EVENT_HANDLER_H__

#include <vector>

#include "Engine/Common/common_definitions.h"
#include "Engine/Utility/pointer.h"
#include "Engine/Event/event.h"
#include "Engine/Event/event_listener.h"

namespace shrine::event
{

template<typename T> struct isListener : isBaseOf<Listener, T> {};

template<typename T> struct isEvent : isBaseOf<IEvent, T> {};

// TODO: Implement Event System
// TODO: Make it concurrent
class SHRINE_API Handler
{
public:
    using listener_pointer = ScopedPointer<Listener>;
    using listener_registry = std::vector<listener_pointer>;
    
private:
    listener_registry m_listenerRegistry;
public:
    template<typename T, typename... Args> 
    enableIf_type<isListener<T>::value, T&> makeListener(Args&&... args) {
        return static_cast<T&>(*m_listenerRegistry.emplace_back(makeScoped<T>(std::forward<Args>(args)...)));
    }

    // Listener drop function, that removes listener from registry
    void popListener();

    // Clears listener registry
    void clearRegistry();

    template<typename E, typename... Args> 
    enableIf_type<isEvent<E>::value> callEvent(Args&&... args) {
        E event(std::forward<Args>(args)...); // SFINAE for IEvent
        for (const listener_pointer& pointer : m_listenerRegistry) {
            Listener& listener = *pointer;
            listener.handleCallbacks(E::eventType(), static_cast<IEvent&>(event));
        }
    }
};

}; // shrine::event

#endif // __SHRINE_ENGINE_EVENTS_EVENT_HANDER_H__