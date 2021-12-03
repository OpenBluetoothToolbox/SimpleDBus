#pragma once

#include <simpledbus/base/BasicInterface.h>

#include <memory>
#include <string>

namespace SimpleDBus {

class Proxy {
  public:
    Proxy(std::shared_ptr<Connection> conn, const std::string& bus_name, const std::string& path);

    std::string path() const;

    const std::map<std::string, std::shared_ptr<Proxy>>& children();
    const std::map<std::string, std::shared_ptr<BasicInterface>>& interfaces();

    virtual std::shared_ptr<BasicInterface> interfaces_create(const std::string& name, Holder options);
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
    virtual void message_handle(Message msg);
    void message_forward(Message& msg);

  protected:
    std::string _path;
    std::string _bus_name;
    std::shared_ptr<Connection> _conn;
    std::map<std::string, std::shared_ptr<BasicInterface>> _interfaces;
    std::map<std::string, std::shared_ptr<Proxy>> _children;
};

}  // namespace SimpleDBus
