#ifndef __SHRINE_ENGINE_CORE_H__
#define __SHRINE_ENGINE_CORE_H__

#if defined(SHR_PLATFORM_UNIX)
    #define SHRINE_API
#elif defined(SHR_PLATFORM_WIN)
    #if defined(SHR_BUILD_DLL)
        #define SHRINE_API __declspec(dllexport)
    #elif defined(SHR_BUILD_STATIC)
        #define SHRINE_API
    #else
        #define SHRINE_API __declspec(dllimport)
    #endif
#endif

#endif // __SHRINE_ENGINE_CORE_H__