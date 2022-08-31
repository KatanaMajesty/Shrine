cmake_minimum_required(VERSION 3.20)
project(sandbox VERSION 0.0.1 LANGUAGES CXX)

add_executable(sandbox sandbox.cpp)
target_include_directories(sandbox PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../ShrineCore/include)
target_link_libraries(sandbox
    shrine-core
)