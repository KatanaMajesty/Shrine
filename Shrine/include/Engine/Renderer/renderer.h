#ifndef __SHRINE_ENGINE_RENDERER_RENDERER_H__
#define __SHRINE_ENGINE_RENDERER_RENDERER_H__

#include "Engine/layer_queue.h"
#include "Engine/core.h"

namespace shrine::renderer
{

class SHRINE_API Renderer
{
private:
    shrine::LayerQueue m_Layers;

public:
    void render();
};

}; // shrine::renderer

#endif // __SHRINE_ENGINE_RENDERER_RENDERER_H__