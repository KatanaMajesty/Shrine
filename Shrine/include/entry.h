#ifndef __SHRINE_ENTRY_H__
#define __SHRINE_ENTRY_H__

#include "Engine/application.h"
#include "Engine/Utility/logger.h"

namespace shrine
{

    extern shrine::SharedPointer<Application> Main(int argc, char** argv);
    
}; // shrine

int main(int argc, char** argv)
{
    shrine::SharedPointer<shrine::Application> app = shrine::Main(argc, argv);
    shrine::Logger::tryBoundLog(shrine::LogLevel::Debug, "Cretaed shrine application. Starting now...");
    app->run();
    return 0;
}

#endif // __SHRINE_ENTRY_H__