#pragma once

#include <simpledbus/advanced/Interface.h>
#include <simpledbus/advanced/Callback.h>

#include <memory>
#include <string>

namespace SimpleDBus {

class Proxy {
  public:
    Proxy(std::shared_ptr<Connection> conn, const std::string& bus_name, const std::string& path);

    std::string path() const;

    const std::map<std::string, std::shared_ptr<Proxy>>& children();
    const std::map<std::string, std::shared_ptr<Interface>>& interfaces();

    virtual std::shared_ptr<Interface> interfaces_create(const std::string& name);
    virtual std::shared_ptr<Proxy> path_create(const std::string& path);

    // ----- INTERFACE HANDLING -----
    size_t interfaces_count() const;
    bool interfaces_loaded() const;
    void interfaces_load(Holder managed_interfaces);
    void interfaces_reload(Holder managed_interfaces);
    void interfaces_unload(Holder removed_interfaces);

    // ----- CHILD HANDLING -----
    void path_add(const std::string& path, Holder managed_interfaces);
    bool path_remove(const std::string& path, Holder removed_interfaces);
    bool path_prune();

    // ----- MESSAGE HANDLING -----
    void message_forward(Message& msg);

    // ----- CALLBACKS -----
    Callback<std::function<void(std::string)>, std::string> on_child_created;
    Callback<std::function<void(std::string)>, std::string> on_child_signal_received;

  protected:
    std::string _path;
    std::string _bus_name;
    std::shared_ptr<Connection> _conn;
    std::map<std::string, std::shared_ptr<Interface>> _interfaces;
    std::map<std::string, std::shared_ptr<Proxy>> _children;
};

}  // namespace SimpleDBus
