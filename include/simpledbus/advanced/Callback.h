#pragma once

#include <functional>
#include <memory>
#include <mutex>
#include <string>

namespace SimpleDBus {

template <typename T, typename... params>
class Callback {
  public:
    void load(T callback);
    void unload();
    void operator()(params... args);

  protected:
    std::recursive_mutex _mutex;
    T _callback;
};

}  // namespace SimpleDBus
