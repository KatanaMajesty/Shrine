#include <shrine.h>
#include <shrine_events.h>

namespace shrine
{

class WindowListener
{
public:
    WindowListener() = default;
    ~WindowListener() = default;

    bool onKeyPressedEvent(event::KeyPressedEvent& event) {
        if (event.getKeycode() == SHR_KEY_ESCAPE) {
            event.getWindow().close();
            return true;
        }
        return false;
    }

    bool onWindowClosed(event::WindowClosedEvent& event) {
        SHR_LOG(SHR_LOGGER_USER, LogLevel::Trace, "Window \"{}\" will be closed!", event.getWindow().getAttributes().title);

        if (false) {
            event.cancelled = true;
        }

        return true; // mark event as handled
    }
};

class SandboxApp : public Application
{
private:
    WindowListener m_windowListener;

public:
    SandboxApp() : Application() 
    {
    }

    virtual void run() override {        
        getEventBus().subscribe(&m_windowListener, &WindowListener::onKeyPressedEvent);
        getEventBus().subscribe(&m_windowListener, &WindowListener::onWindowClosed);
        getWindow().open();
    }
};

SharedPointer<Application> Main(int argc, char** argv) {
    SharedPointer<SandboxApp> app = makeShared<SandboxApp>();
    Logger::createLogger<Logger>(SHR_LOGGER_USER, "USER_LOGGER");
    Logger::getLogger(SHR_LOGGER_USER)->setLevel(LogLevel::Trace);
    SHR_LOG(SHR_LOGGER_USER, LogLevel::Trace, "Hello, Log!");
    return app;
}

}; // shrine