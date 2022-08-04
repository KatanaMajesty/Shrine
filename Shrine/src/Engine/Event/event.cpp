#include "Engine/Event/event.h"

namespace shrine::event
{

IEvent::IEvent(uint16_t categories) { m_Categories |= categories; }

bool IEvent::ofCategory(uint16_t category) { return (m_Categories & category) == category; }

}; // shrine::event