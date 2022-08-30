#include "Engine/Event/event.h"

namespace shrine::event
{

Event::Event(uint16_t categories) 
{ 
    m_categories |= categories; 
}

bool Event::ofCategory(uint16_t category) { 
    return (m_categories & category) == category; 
}

CancellableEvent::CancellableEvent(uint16_t categories) 
    : Event(m_categories) 
{
}

}; // shrine::event