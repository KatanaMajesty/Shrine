#include <memory>

#include <shrine.h>
#include <Engine/Event/key_pressed_event.h>
#include <Engine/Event/key_released_event.h>
#include <Engine/Event/key_repeated_event.h>

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
            addCallback(Type::KEY_PRESSED, MyListener::onKeyPressed);
            addCallback(Type::KEY_RELEASED, MyListener::onKeyReleased);
            addCallback(Type::KEY_REPEATED, MyListener::onKeyRepeated);
        }

    private:
        static bool onKeyPressed(IEvent& e) {
            KeyPressedEvent& event = static_cast<KeyPressedEvent&>(e); // assert this, should be okay
            if (event.getKeycode() == SHR_KEY_ESCAPE) {
                if (event.ofCategory(CATEGORY_KEYBOARD_EVENT)) {
                    Logger::tryBoundLog(LogLevel::Debug, "KeyPressedEvent is in Keyboard category!");
                }
                return true;
            }
            return false;
        }

        static bool onKeyReleased(IEvent& e) {
            KeyRepeatedEvent& event = static_cast<KeyRepeatedEvent&>(e); // assert this, should be okay
            if (event.getKeycode() == SHR_KEY_ESCAPE) {
                if (!event.ofCategory(CATEGORY_WINDOW_EVENT)) {
                    Logger::tryBoundLog(LogLevel::Debug, "KeyRepeatedEvent is not in Window category!");
                }
                event.getWindow().close();
                return true;
            }
            return false;
        }

        static bool onKeyRepeated(IEvent& e) {
            KeyRepeatedEvent& event = static_cast<KeyRepeatedEvent&>(e); // assert this, should be okay
            Logger::tryBoundLog(LogLevel::Debug, "KeyRepeatedEvent: key {} is being repeated", event.getKeycode());
            return false; // shouldn't be handled, just logged
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
        getWindow().getEventHandler().makeListener<event::MyListener>(); // register our listener
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