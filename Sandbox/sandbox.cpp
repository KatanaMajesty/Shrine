#include <shrine.h>

namespace shrine
{

class SandboxApp : public Application
{
public:
    SandboxApp() : Application() 
    {
    }

    virtual void run() override
    {        
        getWindow().open();
    }

    
};

SharedPointer<Application> Main(int argc, char** argv)
{
    SharedPointer<SandboxApp> app = makeShared<SandboxApp>();
    Logger::createLogger<Logger>(SHR_LOGGER_USER, "USER_LOGGER");
    Logger::getLogger(SHR_LOGGER_USER)->setLevel(LogLevel::Trace);
    SHR_LOG(SHR_LOGGER_USER, LogLevel::Debug, "Hello, World!");
    return app;

}

}; // shrine