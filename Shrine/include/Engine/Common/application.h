#ifndef __SHRINE_ENGINE_APPLICATION_H__
#define __SHRINE_ENGINE_APPLICATION_H__

#include <string>

#include "Engine/Common/common_definitions.h"
#include "Engine/Common/window.h"
#include "Engine/Utility/logger.h"

namespace shrine
{

class SHRINE_API Application
{
private:
    ref_t<Logger> m_logger;
    Window m_window;

protected:
    inline Window& getWindow() { return m_window; }

public:

    Application();
    Application(const Application&) = delete;
    virtual ~Application() = default;

    virtual void run() = 0;

    // This member-function will be used to create a logger when constructing an application
    virtual ref_t<Logger> createLogger(const std::string& identifier);

    virtual inline Logger& getLogger() { return m_logger.get(); }
    virtual inline const Logger& getLogger() const { return m_logger.get(); }
};

}; // shrine

#endif // __SHRINE_ENGINE_APPLICATION_H__


