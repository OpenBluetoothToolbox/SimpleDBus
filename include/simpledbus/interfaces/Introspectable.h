#pragma once

#include <simpledbus/base/Interface.h>

namespace SimpleDBus {

class Holder;
class Connection;

class Introspectable : public Interface {
  public:
    Introspectable(std::shared_ptr<Connection> conn, std::string bus_name, std::string path);
    virtual ~Introspectable();

    // Names are made matching the ones from the DBus specification
    Holder Introspect();
};

}  // namespace SimpleDBus
