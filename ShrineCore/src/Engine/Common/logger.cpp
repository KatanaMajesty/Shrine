#include "Engine/Common/logger.h"

namespace shrine
{

bool Logger::s_initialized = false;
std::string Logger::s_pattern = "%^[%n] [%T %l]:%$ %v";

}; // shrine