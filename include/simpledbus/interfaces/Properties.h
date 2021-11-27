#pragma once

#include <simpledbus/base/Interface.h>

#include <functional>

namespace SimpleDBus {

class Holder;
class Connection;

class Properties : public Interface {
  public:
    Properties(std::shared_ptr<Connection> conn, std::string bus_name, std::string path);
    virtual ~Properties();

    // Names are made matching the ones from the DBus specification
    Holder Get(std::string interface, std::string name);
    Holder GetAll(std::string interface);
    void Set(std::string interface, std::string name, Holder value);
};

}  // namespace SimpleDBus
