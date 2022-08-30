#ifndef __SHRINE_ENGINE_GRAPHICS_RENDERER_H__
#define __SHRINE_ENGINE_GRAPHICS_RENDERER_H__

#include "Engine/Graphics/layer_queue.h"
#include "Engine/Common/common_definitions.h"

namespace shrine
{

class SHRINE_API Renderer
{
private:
    shrine::LayerQueue m_Layers;

public:
    void render();
};

}; // shrine

#endif // __SHRINE_ENGINE_GRAPHICS_RENDERER_H__