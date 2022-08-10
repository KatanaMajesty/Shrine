#ifndef __SHRINE_ENGINE_RENDERER_RENDERER_H__
#define __SHRINE_ENGINE_RENDERER_RENDERER_H__

#include "Engine/Renderer/layer_queue.h"
#include "Engine/Common/common_definitions.h"

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