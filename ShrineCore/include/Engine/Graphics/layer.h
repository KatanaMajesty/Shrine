#ifndef __SHRINE_ENGINE_GRAPHICS_LAYER_H__
#define __SHRINE_ENGINE_GRAPHICS_LAYER_H__

#include "Engine/Event/event_bus.h"

namespace shrine
{

class Layer
{
public:
    using event_bus_type = event::EventBus;

private:
    std::string m_name;
    event_bus_type& m_eventBus;

public:
    Layer(event_bus_type& eventBus, const std::string& layerName = "Unnamed layer");
    virtual ~Layer() = default;

    virtual void attach() {};
    virtual void update() {};
    virtual void detatch() {};

    template<typename Receiver, typename EventType>
    void subscribe(event_bus_type::listener_callable<Receiver, EventType> callable) {
        m_eventBus.subscribe(static_cast<Receiver*>(this), callable);
    }

    template<typename Receiver, typename EventType>
    void unsubscribe(event_bus_type::listener_callable<Receiver, EventType> callable) {
        m_eventBus.unsubscribe(static_cast<Receiver*>(this), callable);
    }

    inline const std::string& getName() const { return m_name; }
};

}; // shrine

#endif // __SHRINE_ENGINE_GRAPHICS_LAYER_H__