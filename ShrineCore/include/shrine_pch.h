#ifndef __SHRINE_PRECOMPILED_HEADER_H__
#define __SHRINE_PRECOMPILED_HEADER_H__

#include <string>
#include <typeindex>
#include <type_traits>
#include <iostream>
#include <functional>
#include <string_view>
#include <utility>
#include <thread>

// STL containers
#include <map>
#include <unordered_map>
#include <vector>
#include <queue>
#include <stack>
#include <list>

#include <memory>
#include <filesystem> // needed in assert

// Memory management part
#include <cstddef>
#include <cstdlib>
#include <cassert>
#include <cstring>

// OpenGL stuff
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// SPDLOG stuff
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/ostr.h> // must be included

#endif // __SHRINE_PRECOMPILED_HEADER_H__