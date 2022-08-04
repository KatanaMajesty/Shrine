cmake_minimum_required(VERSION 3.20)
project(shrine VERSION 0.0.1 LANGUAGES CXX)

SET(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared libraries")

add_subdirectory(Vendor/glfw)
add_subdirectory(Vendor/spdlog)
find_package(GLEW REQUIRED)

file(GLOB_RECURSE SOURCE src/*.cpp)

add_library(shrine SHARED ${SOURCE})

if (UNIX)
    target_compile_definitions(shrine PUBLIC SHR_PLATFORM_UNIX)
elseif(WIN32)
    target_compile_definitions(shrine PUBLIC SHR_PLATFORM_WIN)
endif()

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