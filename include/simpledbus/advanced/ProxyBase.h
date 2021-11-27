#pragma once

#include <simpledbus/base/Interface.h>

#include <memory>
#include <string>

namespace SimpleDBus {

class ProxyBase {
  public:
    ProxyBase(std::shared_ptr<Connection> conn, const std::string& bus_name, const std::string& path);

    virtual std::shared_ptr<Interface> interfaces_create(const std::string& name, Holder options);

    // ----- INTERFACE HANDING -----
    size_t interfaces_count() const;
    bool interfaces_loaded() const;
    void interfaces_load(Holder managed_interfaces);
    void interfaces_reload(Holder managed_interfaces);
    void interfaces_unload(Holder removed_interfaces);

  protected:
    std::string _path;
    std::string _bus_name;
    std::shared_ptr<Connection> _conn;
    std::map<std::string, std::shared_ptr<Interface>> _interfaces;
};

}  // namespace SimpleDBus
