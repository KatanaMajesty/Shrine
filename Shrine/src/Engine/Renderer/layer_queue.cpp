#include "Engine/Renderer/layer_queue.h"

namespace shrine
{
    void LayerQueue::pop() { m_Container.pop_back(); }
    LayerQueue::iterator LayerQueue::begin() { return m_Container.begin(); }
    LayerQueue::iterator LayerQueue::end() { return m_Container.end(); }
    
}; // shrine