#ifndef __SHRINE_ENGINE_WINDOW__
#define __SHRINE_ENGINE_WINDOW__

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Engine/core.h"
#include "Engine/Utility/logger.h"
#include "Engine/Renderer/renderer.h"
#include "Engine/Event/event_handler.h"

namespace shrine
{

struct SHRINE_API WindowAttributes
{
    std::string name;
    uint32_t width;
    uint32_t height;

    WindowAttributes(const std::string& name = "Shrine Application", 
                    uint32_t width = 1280, u_int32_t height = 720);
};

class SHRINE_API Window
{
private:
    GLFWwindow* m_Window;
    bool isVsync = true; // true by default (maybe change in future) // should be moved to WindowAttributes
    const WindowAttributes m_Attributes;
    renderer::Renderer m_Renderer;

public:
    event::Handler m_EventHandler; // temp
    Window(const WindowAttributes& attributes);
    ~Window();

    inline const WindowAttributes& attributes() const { return m_Attributes; }

    void open();
    void close();

    renderer::Renderer& getRenderer();
    const renderer::Renderer& getRenderer() const;
private:
    void updateGLFWContext();
    void updateVsync(bool isVsync);
    bool shouldBeClosed() const;
};

// TODO: Implement window registry, that will hold all currently opened and bound to Shrine windows
//      It should be responsible for opening, closing and returning window contexts to API/Engine
//      Maybe it should be moved into separate file/class called Registry<T>?
class WindowRegistry
{
    // No implementation
};


} // shrine

#endif // __SHRINE_ENGINE_WINDOW__