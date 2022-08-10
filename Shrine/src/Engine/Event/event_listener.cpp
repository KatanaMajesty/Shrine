#include "Engine/Event/event_listener.h"

namespace shrine::event
{

void Listener::addCallback(Listener::event_type type, Listener::callback_type callback) {
    m_callbacks.insert_or_assign(type, callback);
}

bool Listener::handleCallbacks(event_type type, IEvent& event) const {
    Listener::event_callbacks::const_iterator iter = m_callbacks.find(type);
    if (iter != m_callbacks.end()) {
        return std::invoke(iter->second, event); // call a callback to event
    }
    return true; // all event_callbacks were handled correctly
}

}; // shrine::event