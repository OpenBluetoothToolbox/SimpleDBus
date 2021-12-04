#pragma once

#include <simpledbus/base/Connection.h>

#include <functional>
#include <memory>
#include <string>

namespace SimpleDBus {

class Holder;
class Connection;

class Introspectable {
  public:
    Introspectable(std::shared_ptr<Connection> conn, std::string bus_name, std::string path);
    virtual ~Introspectable();

    // Names are made matching the ones from the DBus specification
    Holder Introspect();

  protected:
    std::string _path;
    std::string _bus_name;
    std::string _interface_name;
    std::shared_ptr<Connection> _conn;
};

}  // namespace SimpleDBus
