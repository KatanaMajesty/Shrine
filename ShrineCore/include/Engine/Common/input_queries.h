#ifndef __SHRINE_ENGINE_COMMON_INPUT_QUERIES_H__
#define __SHRINE_ENGINE_COMMON_INPUT_QUERIES_H__

#include "Engine/Common/application.h"
#include "Engine/Common/common_definitions.h"
#include "Engine/Utility/keyboard.h"

namespace shrine
{

class ShrineIO
{
private:
    static ScopedPointer<ShrineIO> s_instance;
    SharedPointer<Application> m_application;

private:
    ShrineIO(SharedPointer<Application> application);

public:
    ~ShrineIO() = default;

    inline static void initialize(SharedPointer<Application> application) {
        s_instance = ScopedPointer<ShrineIO>(new ShrineIO(application));
    }

    inline static ShrineIO& get() {
        SHR_ASSERT(s_instance);
        return *s_instance.get();
    }

    bool isKeyPressed(const Keycode key) {
        GLFWwindow* context = m_application->getWindow().getGLFWwindow();
        uint32_t state = glfwGetKey(context, static_cast<uint32_t>(key));
        return GLFW_PRESS == state;
    }


    bool isKeyReleased(const Keycode key) {
        GLFWwindow* context = m_application->getWindow().getGLFWwindow();
        uint32_t state = glfwGetKey(context, static_cast<uint32_t>(key));
        return GLFW_RELEASE == state;
    }

    bool isKeyHeld(const Keycode key) {
        GLFWwindow* context = m_application->getWindow().getGLFWwindow();
        uint32_t state = glfwGetKey(context, static_cast<uint32_t>(key));
        return GLFW_REPEAT == state;
    }

}; // ShrineIO class

}; // shrine

#endif // __SHRINE_ENGINE_COMMON_INPUT_QUERIES_H__