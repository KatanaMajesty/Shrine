#include <shrine.h>
#include <shrine_events.h>

namespace shrine
{

class WindowListener
{
public:
    WindowListener() = default;
    ~WindowListener() = default;

    
};

class SandboxLayer : public Layer
{
public:
    SandboxLayer(event_bus_type& eventBus) 
        : Layer(eventBus, "Sandbox Layer") 
    {
        subscribe(&SandboxLayer::onKeyPressedEvent);
        subscribe(&SandboxLayer::onWindowClosed);
    }
    ~SandboxLayer() = default;

    virtual void attach() override {
        SHR_LOG_CORE_DEBUG("(Layer \"{}\"): Successfully attached!", getName());
    }

    virtual void update() override {
        SHR_LOG_CORE_DEBUG("(Layer \"{}\"): Updated!", getName());
    }

    virtual void detatch() override {
        SHR_LOG_CORE_DEBUG("(Layer \"{}\"): Successfully detatched!", getName());
    }

    bool onKeyPressedEvent(event::KeyPressedEvent& event) {
        Window& window = event.getWindow();
        if (event.getKeycode() == Keycode::Escape) {
            window.close();
            return true;
        } else if (event.getKeycode() == Keycode::F11) {
            WindowAttributes& attr = window.getAttributes();
            attr.fullscreen = !attr.fullscreen;
            if (attr.fullscreen) {
                window.goFullscreen();
            } else {
                window.goWindowed();
            }
            return true;
        }
        return false;
    }

    bool onWindowClosed(event::WindowClosedEvent& event) {
        SHR_LOG("USER_LOGGER", LogLevel::Trace, "Window \"{}\" will be closed!", event.getWindow().getAttributes().title);

        return false; // mark event as handled
    }
};

class SandboxApp : public Application
{
private:
    WindowListener m_windowListener;

public:
    SandboxApp() : Application(ApplicationAttributes{.name = "Sandbox Application"}) 
    {
        event_bus_type& eventBus = getEventBus();

        getWindow().getLayerQueue().pushLayer<SandboxLayer>(eventBus);
    }
};

SharedPointer<Application> Main(int argc, char** argv) {
    SharedPointer<SandboxApp> app = makeShared<SandboxApp>();
    SHR_CREATE_LOGGER("USER_LOGGER", LogLevel::Trace, Logger::getDefaultPattern());
    SHR_LOG("USER_LOGGER", LogLevel::Trace, "Hello, Log!");
    return app;
}

}; // shrine