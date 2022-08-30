#include "Engine/Graphics/layer.h"

namespace shrine
{

Layer::Layer(event_bus_type& eventBus, const std::string& layerName)
    : m_name(layerName)
    , m_eventBus(eventBus)
{
}

}; // shrine