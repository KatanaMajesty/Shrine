#ifndef __SHRINE_ENGINE_EVENTS_EVENT_BUS_H__
#define __SHRINE_ENGINE_EVENTS_EVENT_BUS_H__

#include "Engine/Common/common_definitions.h"
#include "Engine/Common/logger.h"
#include "Engine/Event/event.h"

namespace shrine::event
{

class SHRINE_API EventSubscriber
{
public:
    EventSubscriber() = default;
    virtual ~EventSubscriber() = default;

    inline bool dispatch(Event& event) {
        return invoke(event);
    }
private:
    virtual bool invoke(Event& event) = 0;
};



template<typename T> struct isEvent : isBaseOf<Event, T> {};



template<typename Receiver, typename EventType>
class EventHandler : public EventSubscriber
{
public:
    using listener_callable = bool(Receiver::*)(EventType&);

public:
    EventHandler(Receiver* receiver, listener_callable callable)
        : m_receiver(receiver), m_callable(callable)
    {
    }
    virtual ~EventHandler() = default;

private:
    virtual bool invoke(Event& event) override {
        SHR_ASSERT(isEvent<EventType>::value);
        return (m_receiver->*m_callable)(static_cast<EventType&>(event));
    }

    bool operator==(EventHandler& other) const { return m_receiver == other.m_receiver && m_callable == other.m_callable; }

    bool operator==(Receiver* other) const { return m_receiver == other; }

private:
    Receiver* m_receiver;
    listener_callable m_callable;
};



class SHRINE_API EventBus
{
public:
    template<typename Receiver, typename EventType> using listener_callable = bool(Receiver::*)(EventType&);
    using subscriber_type = ScopedPointer<EventSubscriber>;
    using subscribers = std::vector<subscriber_type>;

private:
    std::unordered_map<std::type_index, subscribers> m_eventMap;

public:
    EventBus() = default;
    EventBus(const EventBus&) = delete;
    EventBus& operator=(const EventBus&) = delete;

    template<typename EventType>
    enableIf_type<isEvent<EventType>::value> publish(EventType& event) {
        auto entry = m_eventMap.find(typeid(EventType));
        if (entry != m_eventMap.end()) {
            subscribers& list = entry->second;
            // we should iterate from end to beginning, so that all events are handled in order
            for (subscribers::reverse_iterator it = list.rbegin(); it != list.rend(); ++it) {
                if ((*it)->dispatch(event)) { // if handled - break the loop
                    SHR_LOG_CORE_TRACE("{}: successfully handled by receiver!", event);
                    break;
                }
            }
        }
    }

    template<typename Receiver, typename EventType> 
    enableIf_type<isEvent<EventType>::value> subscribe(Receiver* receiver, listener_callable<Receiver, EventType> callable) {
        subscribers& list = m_eventMap[typeid(EventType)];
        list.emplace_back(makeScoped<EventHandler<Receiver, EventType>>(receiver, callable));
    }

    template<typename Receiver, typename EventType>
    enableIf_type<isEvent<EventType>::value> unsubscribe(Receiver* receiver, listener_callable<Receiver, EventType> callable) {
        auto entry = m_eventMap.find(typeid(EventType));
        if (entry != m_eventMap.end()) {
            const EventHandler<Receiver, EventType> comparator;
            subscribers& list = entry->second;

            list.erase(std::remove_if(list.begin(), list.end(), [&](const subscriber_type& value) -> bool {
                return (*static_cast<EventHandler<Receiver, EventType>*>(value.get())) == comparator;
            }), list.end());
        }
    }

    template<typename Receiver>
    void unsubscribeAll(Receiver* receiver) {
        for (auto& [_, list] : m_eventMap) {
            list.erase(std::remove_if(list.begin(), list.end(), [&](const subscriber_type& value) {
                return (*static_cast<EventHandler<Receiver, Event>*>(value.get())) == receiver;
            }), list.end());
        }
    }
};



}; // shrine::event

#endif // __SHRINE_ENGINE_EVENTS_EVENT_BUS_H__