#pragma once

#include <functional>
#include <memory>
#include <mutex>
#include <atomic>

namespace SimpleDBus {

template <typename T, typename... params>
class Callback {
  public:
    void load(T callback);
    void unload();
    void operator()(params... args);

  protected:
    T _callback;
    std::recursive_mutex _mutex;
    std::atomic_bool _is_running;
};

}  // namespace SimpleDBus
