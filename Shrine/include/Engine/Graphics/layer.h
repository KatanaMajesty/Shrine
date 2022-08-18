#ifndef __SHRINE_ENGINE_GRAPHICS_LAYER_H__
#define __SHRINE_ENGINE_GRAPHICS_LAYER_H__

namespace shrine
{

class Layer
{
public:
    Layer(const std::string& layerName = "Unnamed layer");
    virtual ~Layer() = default;

    virtual void update() {};
    // TODO: Implement Event System support
};

}; // shrine

#endif // __SHRINE_ENGINE_GRAPHICS_LAYER_H__