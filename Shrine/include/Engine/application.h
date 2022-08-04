#ifndef __SHRINE_ENGINE_APPLICATION_H__
#define __SHRINE_ENGINE_APPLICATION_H__

#include <string>

#include "Engine/core.h"
#include "Engine/window.h"
#include "Engine/Utility/logger.h"

namespace shrine
{

class SHRINE_API Application
{
private:
    Logger m_Logger;
    Window m_Window;

protected:
    inline Window& getWindow() { return m_Window; }

public:

    Application();
    Application(const Application&) = delete;
    virtual ~Application() = default;

    virtual void run() = 0;

    virtual Logger&         getLogger();
    virtual const Logger&   getLogger() const;
};

}; // shrine

#endif // __SHRINE_ENGINE_APPLICATION_H__


