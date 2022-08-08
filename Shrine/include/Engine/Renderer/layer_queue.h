#ifndef __SHRINE_ENGINE_LAYER_QUEUE_H__
#define __SHRINE_ENGINE_LAYER_QUEUE_H__

#include <vector>

#include "Engine/Renderer/layer.h"

namespace shrine
{

class LayerQueue
{
public:
    using container = std::vector<Layer>;
    using iterator = container::iterator;

private:
    container m_Container;

public:
    template<typename T> void push(T&& layer) { m_Container.push_back(std::forward<T>(layer)); }
    void pop();
    iterator begin();
    iterator end();
};

}; // shrine

#endif // __SHRINE_ENGINE_LAYER_QUEUE_H__