#pragma once

#include <simpledbus/base/BasicInterface.h>

#include <functional>

namespace SimpleDBus {

namespace Interfaces {

class Properties : public BasicInterface {
  public:
    Properties(std::shared_ptr<Connection> conn, std::string bus_name, std::string path);
    virtual ~Properties();

    // Names are made matching the ones from the DBus specification
    Holder Get(std::string interface, std::string name);
    Holder GetAll(std::string interface);
    void Set(std::string interface, std::string name, Holder value);
};

}  // namespace Interfaces

}  // namespace SimpleDBus
