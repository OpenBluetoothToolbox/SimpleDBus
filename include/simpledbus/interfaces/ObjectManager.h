#pragma once

#include <simpledbus/base/Connection.h>

#include <functional>
#include <memory>
#include <string>

namespace SimpleDBus {

class ObjectManager {
  public:
    ObjectManager(std::shared_ptr<Connection> conn, std::string bus_name, std::string path);
    ~ObjectManager();

    // Names are made matching the ones from the DBus specification
    Holder GetManagedObjects(bool use_callbacks = false);
    std::function<void(std::string path, Holder options)> InterfacesAdded;
    std::function<void(std::string path, Holder options)> InterfacesRemoved;

    bool process_received_signal(Message& message);

  protected:
    std::string _path;
    std::string _bus_name;
    std::string _interface_name;
    std::shared_ptr<Connection> _conn;
};

}  // namespace SimpleDBus
