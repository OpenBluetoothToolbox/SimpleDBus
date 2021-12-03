#pragma once

#include <simpledbus/base/Connection.h>

#include <memory>
#include <string>

namespace SimpleDBus {

class BasicInterface {
  public:
    BasicInterface(std::shared_ptr<Connection> conn, const std::string& bus_name, const std::string& path,
                   const std::string& interface_name);

    virtual ~BasicInterface() = default;

    void load(Holder options);
    void unload();
    bool is_loaded() const;

  protected:
    bool _loaded{true};

    std::string _path;
    std::string _bus_name;
    std::string _interface_name;
    std::shared_ptr<Connection> _conn;
};

}  // namespace SimpleDBus
