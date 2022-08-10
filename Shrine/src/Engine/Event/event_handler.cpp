#include "Engine/Event/event_handler.h"

namespace shrine::event
{

void Handler::popListener() { m_listenerRegistry.pop_back(); }

void Handler::clearRegistry() { m_listenerRegistry.clear(); }

}; // shrine::event