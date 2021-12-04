#pragma once

#include <simpledbus/base/Connection.h>

#include <functional>
#include <memory>
#include <string>
namespace SimpleDBus {

namespace Interfaces {

class Properties {
  public:
    Properties(std::shared_ptr<Connection> conn, std::string bus_name, std::string path);
    virtual ~Properties();

    // Names are made matching the ones from the DBus specification
    Holder Get(std::string interface, std::string name);
    Holder GetAll(std::string interface);
    void Set(std::string interface, std::string name, Holder value);

    protected:
    std::string _path;
    std::string _bus_name;
    std::string _interface_name;
    std::shared_ptr<Connection> _conn;
};

}  // namespace Interfaces

}  // namespace SimpleDBus
