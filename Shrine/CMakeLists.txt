cmake_minimum_required(VERSION 3.20)
project(shrine VERSION 0.0.1 LANGUAGES CXX)

set(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared libraries")
set(SHR_CXX_STD 20) # Use C++20

add_subdirectory(Vendor/glfw)
add_subdirectory(Vendor/spdlog)
find_package(GLEW REQUIRED)

file(GLOB_RECURSE SOURCE src/*.cpp)

set(CMAKE_CXX_STANDARD ${SHR_CXX_STD})

add_library(shrine SHARED ${SOURCE})

if (UNIX)
    target_compile_definitions(shrine PUBLIC SHR_PLATFORM_UNIX)
elseif(WIN32)
    target_compile_definitions(shrine PUBLIC SHR_PLATFORM_WIN)
endif()

# Shrine-specific options and definitions
option(SHR_DEBUG "Enable debug mode" ON)

if (SHR_DEBUG)
    message(STATUS "Shrine debug mode enabled")
    target_compile_definitions(shrine PUBLIC SHR_DEBUG)
endif()

# Linking part
target_include_directories(shrine
    PRIVATE ${GLEW_INCLUDE_DIRS}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/glfw/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Vendor/spdlog/include)

target_link_libraries(shrine 
    PUBLIC GLEW::GLEW
    PUBLIC GL
    PUBLIC glfw
    PUBLIC spdlog)