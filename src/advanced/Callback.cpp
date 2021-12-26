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
    if (_is_running) {
        _delete_requested = true;
    } else {
        _mutex.lock();
        _callback = nullptr;
        _delete_requested = false;
        _mutex.unlock();
    }
}

template <typename T, typename... params>
void Callback<T, params...>::operator()(params... args) {
    _is_running = true;
    _mutex.lock();
    if (_callback && !_delete_requested) {
        _callback(args...);
    }
    if (_delete_requested) {
        _callback = nullptr;
        _delete_requested = false;
    }
    _mutex.unlock();
    _is_running = false;
}

template <typename T, typename... params>
bool Callback<T, params...>::is_loaded() {
    bool loaded = false;
    _mutex.lock();
    loaded = _callback != nullptr;
    _mutex.unlock();
    return loaded;
}

template <typename T, typename... params>
bool Callback<T, params...>::is_running() {
    return _is_running;
}

template <typename T, typename... params>
bool Callback<T, params...>::is_delete_requested() {
    return _delete_requested;
}

// Instantiations

namespace SimpleDBus {

template class Callback<std::function<void()>>;
template class Callback<std::function<void(std::string)>, std::string>;

}  // namespace SimpleDBus
