#include <simpledbus/advanced/Callback.h>

using namespace SimpleDBus;

template <typename T, typename... params>
void Callback<T, params...>::load(T callback) {
    _mutex.lock();
    _callback = callback;
    _mutex.unlock();
}

template <typename T, typename... params>
void Callback<T, params...>::unload() {
    _mutex.lock();
    _callback = nullptr;
    _mutex.unlock();
}

template <typename T, typename... params>
void Callback<T, params...>::operator()(params... args) {
    _mutex.lock();
    if (_callback) {
        _callback(args...);
    }
    _mutex.unlock();
}

// Instantiations

namespace SimpleDBus {

template class Callback<std::function<void()>>;
template class Callback<std::function<void(std::string)>, std::string>;

}  // namespace SimpleDBus
