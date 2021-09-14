#pragma once
#include <functional>
#include <string>

#include "../base/Connection.h"
#include "../base/Holder.h"
#include "../base/Message.h"

namespace SimpleDBus {

class Holder;
class Connection;

class Introspectable {
  private:
    const std::string _interface;

    std::string _path;
    std::string _service;
    Connection* _conn;

  public:
    Introspectable(Connection* conn, std::string service, std::string path);
    virtual ~Introspectable();

    // Names are made matching the ones from the DBus specification
    Holder Introspect();
};

}  // namespace SimpleDBus