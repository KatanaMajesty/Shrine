#include "Engine/Common/input_queries.h"

namespace shrine
{

ScopedPointer<ShrineIO> ShrineIO::s_instance = { nullptr };

ShrineIO::ShrineIO(SharedPointer<Application> application) 
    : m_application(application)
{
}

}; // shrine