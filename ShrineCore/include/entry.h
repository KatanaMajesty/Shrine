#ifndef __SHRINE_ENTRY_H__
#define __SHRINE_ENTRY_H__

#include "Engine/Common/application.h"
#include "Engine/Common/logger.h"

namespace shrine
{

    extern shrine::SharedPointer<Application> Main(int argc, char** argv);
    
}; // shrine

int main(int argc, char** argv)
{
    shrine::Logger::initialize();
    SHR_CREATE_LOGGER("ENGINE_LOGGER", shrine::LogLevel::Trace, shrine::Logger::getDefaultPattern());
    shrine::SharedPointer<shrine::Application> app = shrine::Main(argc, argv);
    app->run();
    return 0;
}

#endif // __SHRINE_ENTRY_H__