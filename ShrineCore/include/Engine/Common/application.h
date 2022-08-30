#ifndef __SHRINE_ENGINE_COMMON_APPLICATION_H__
#define __SHRINE_ENGINE_COMMON_APPLICATION_H__

#include "Engine/Common/common_definitions.h"
#include "Engine/Common/window.h"
#include "Engine/Common/logger.h"
#include "Engine/Event/event_bus.h"

int main(int, char**);

namespace shrine
{

struct SHRINE_API ApplicationAttributes
{
    std::string name;
};

class SHRINE_API Application
{
public:
    using event_bus_type = event::EventBus;

private:
    bool m_glfwInitialized = false;
    ApplicationAttributes m_attributes;
    ScopedPointer<event_bus_type> m_eventBus;
    ScopedPointer<Window> m_window;

public:
    // we need this, so that only the encapsulated main() function was able to run the program, not the API's Main()
    friend int ::main(int, char**);

    /**
     * @brief Construct a new Application object, using Attributes object, containing application-specific parameters
     * 
     * @param attributes an object, that represents application's parameters
     */
    Application(const ApplicationAttributes& attributes);
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;
    virtual ~Application();

    /**
     * @brief Get the Attributes object
     * 
     * @return ApplicationAttributes& 
     */
    inline ApplicationAttributes& getAttributes() { return m_attributes; }
    inline const ApplicationAttributes& getAttributes() const { return m_attributes; }

    /**
     * @brief Get the Event Bus object of application
     * 
     * @return event_bus_type& 
     */
    inline event_bus_type& getEventBus() { return *m_eventBus.get(); }


    /**
     * @brief Get the Window object
     * 
     */
    inline Window& getWindow() { return *m_window.get(); }

    /**
     * @brief Returns true, if GLFW is initiailized. Otherwise - false
     * 
     */
    inline bool isGLFWInitialized() const { return m_glfwInitialized; }
private:
    void run();
};

}; // shrine

#endif // __SHRINE_ENGINE_COMMON_APPLICATION_H__


