#ifndef __SHRINE_ENGINE_APPLICATION_H__
#define __SHRINE_ENGINE_APPLICATION_H__

#include "Engine/Common/common_definitions.h"
#include "Engine/Common/window.h"
#include "Engine/Utility/logger.h"
#include "Engine/Event/event_bus.h"

namespace shrine
{

class SHRINE_API Application
{
public:
    using logger_type = Logger;
    using window_type = Window;
    using event_bus_type = window_type::event_bus_type;

private:
    ref_t<logger_type> m_logger;
    ScopedPointer<event_bus_type> m_eventBus;
    ScopedPointer<window_type> m_window;

public:
    Application();
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;
    virtual ~Application() = default;

    virtual void run() = 0;

    // This member-function will be used to create a logger when constructing an application
    virtual ref_t<Logger> createLogger(const std::string& identifier);

    inline Logger& getLogger() { return m_logger.get(); }
    inline const Logger& getLogger() const { return m_logger.get(); }

    inline Window& getWindow() { return *m_window.get(); }
    inline const Window& getWindow() const { return *m_window.get(); }

    inline event_bus_type& getEventBus() { return *m_eventBus.get() ; }
    inline const event_bus_type& getEventBus() const { return *m_eventBus.get() ; }
};

}; // shrine

#endif // __SHRINE_ENGINE_APPLICATION_H__


