#include "Engine/Event/event.h"

namespace shrine::event
{

IEvent::IEvent(uint16_t categories) { m_categories |= categories; }

bool IEvent::ofCategory(uint16_t category) { return (m_categories & category) == category; }

}; // shrine::event