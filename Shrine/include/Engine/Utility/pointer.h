#ifndef __SHRINE_ENGINE_UTILITY_POINTER__
#define __SHRINE_ENGINE_UTILITY_POINTER__

#include <memory>

namespace shrine
{

template<typename T> using ScopedPointer = std::unique_ptr<T>;
template<typename T> using SharedPointer = std::shared_ptr<T>;
template<typename T> using WeakPointer = std::weak_ptr<T>;

template<typename T, typename... Args> ScopedPointer<T> makeScoped(Args&&... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T, typename... Args> SharedPointer<T> makeShared(Args&&... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

} // shrine

#endif // __SHRINE_ENGINE_UTILITY_POINTER__