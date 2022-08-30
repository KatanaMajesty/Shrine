#ifndef __SHRINE_ENGINE_GRAPHICS_LAYER_QUEUE_H__
#define __SHRINE_ENGINE_GRAPHICS_LAYER_QUEUE_H__

#include "Engine/Graphics/layer.h"

namespace shrine
{

template<typename T>
using isLayer = isBaseOf<Layer, T>;

class LayerQueue
{
public:
    using container = std::vector<ScopedPointer<Layer>>;
    using iterator = container::iterator;
    using reverse_iterator = container::reverse_iterator;

private:
    container m_container;

public:
    LayerQueue() = default;
    ~LayerQueue() {
        for (auto& ptr : m_container) {
            ptr->detatch();
        } 
    }

    template<typename T, typename... Args>
    enableIf_type<isLayer<T>::value> pushLayer(Args&&... args) {
        m_container.emplace_back(makeScoped<T>(std::forward<Args>(args)...));
        m_container.back()->attach();
    }

    inline void popLayer() { 
        m_container.back()->detatch();
        m_container.pop_back(); 
    }

    inline iterator begin() { return m_container.begin(); }
    inline iterator end() { return m_container.end(); }
    inline reverse_iterator rbegin() { return m_container.rbegin(); }
    inline reverse_iterator rend() { return m_container.rend(); }
};

}; // shrine

#endif // __SHRINE_ENGINE_GRAPHICS_LAYER_QUEUE_H__