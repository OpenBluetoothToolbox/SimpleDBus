#pragma once

#include <simpledbus/base/Interface.h>

#include <memory>
#include <string>

namespace SimpleDBus {

class InterfaceHolder {
  public:
    InterfaceHolder(std::shared_ptr<SimpleDBus::Connection> conn, const std::string& bus_name, const std::string& path);

    size_t interfaces_count() const;
    bool interfaces_loaded() const;
    void interfaces_load(SimpleDBus::Holder managed_interfaces);
    void interfaces_reload(SimpleDBus::Holder managed_interfaces);
    void interfaces_unload(SimpleDBus::Holder removed_interfaces);

    virtual std::shared_ptr<SimpleDBus::Interface> interfaces_create(const std::string& name,
                                                                     SimpleDBus::Holder options);

  protected:
    std::string _path;
    std::string _bus_name;
    std::shared_ptr<SimpleDBus::Connection> _conn;
    std::map<std::string, std::shared_ptr<Interface>> _interfaces;
};

}  // namespace SimpleDBus
