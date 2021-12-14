#include <simpledbus/advanced/Callback.h>

using namespace SimpleDBus;

// TODO: Make a complete implementation that allows callback changes to be scheduled to prevent lockups.

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
        _is_running = true;
        _callback(args...);
        _is_running = false;
    }
    _mutex.unlock();
}

// Instantiations

namespace SimpleDBus {

template class Callback<std::function<void()>>;
template class Callback<std::function<void(std::string)>, std::string>;

}  // namespace SimpleDBus
