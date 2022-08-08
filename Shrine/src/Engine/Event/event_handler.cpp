#include "Engine/Event/event_handler.h"

namespace shrine::event
{

void Handler::popListener() { m_ListenerRegistry.pop_back(); }

void Handler::clearRegistry() { m_ListenerRegistry.clear(); }

}; // shrine::event