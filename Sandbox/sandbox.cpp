#include <memory>

#include <shrine.h>
#include <Engine/Event/key_pressed_event.h>

namespace shrine
{

    namespace event
    {

        class MyListener : public Listener
        {
        public:
            MyListener()
            {
                // Constructor may be used for adding callbacks
                addCallback(Type::KEY_PRESSED, MyListener::onKeyPressedEvent);
            }

            static bool onKeyPressedEvent(IEvent& e) {
                KeyPressedEvent& event = static_cast<KeyPressedEvent&>(e); // assert this, should be okay
                std::cout << "Listened to KeyPressed event with key " << event.getKeycode() << std::endl;
                return true;
            }
        };

    }; // event

class SandboxApp : public Application
{
public:
    SandboxApp() : Application() 
    {
    }

    virtual void run() override
    {        
        getWindow().m_EventHandler.makeListener<event::MyListener>(); // register our listener

        getWindow().open();
    }
};

SharedPointer<Application> Main(int argc, char** argv)
{
    SharedPointer<SandboxApp> app = makeShared<SandboxApp>();
    app->getLogger().setLevel(LogLevel::Trace);
    app->getLogger().log(LogLevel::Debug, "Hello, World!");
    Logger::bindLogger(app->getLogger());
    return app;
}

}; // shrine