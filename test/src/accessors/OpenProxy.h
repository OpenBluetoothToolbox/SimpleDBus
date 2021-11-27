#pragma once

#include <simpledbus/advanced/Proxy.h>

namespace SimpleDBus {

class OpenProxy : public Proxy {
  public:
    OpenProxy(std::shared_ptr<SimpleDBus::Connection> conn, const std::string& bus_name, const std::string& path)
        : Proxy(conn, bus_name, path){};
    ~OpenProxy() {}

    const std::map<std::string, std::shared_ptr<Proxy>>& children() { return _children; }

    const std::map<std::string, std::shared_ptr<Interface>>& interfaces() { return _interfaces; };

    std::shared_ptr<Proxy> path_create(const std::string& path) override {
        auto child = std::make_shared<OpenProxy>( _conn, _bus_name, path);
        return std::static_pointer_cast<Proxy>(child);
    }
};

};  // namespace SimpleDBus
