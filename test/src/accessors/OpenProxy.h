#pragma once

#include <simpledbus/advanced/Proxy.h>

namespace SimpleDBus {

class OpenProxy : public Proxy {
  public:
    OpenProxy(const std::string& bus_name, const std::string& path, std::shared_ptr<SimpleDBus::Connection> conn)
        : Proxy(bus_name, path, conn){};
    ~OpenProxy() {}

    const std::map<std::string, std::shared_ptr<Proxy>>& children() { return _children; }

    const std::map<std::string, std::shared_ptr<Interface>>& interfaces() { return _interfaces; };

    std::shared_ptr<Proxy> create_child(const std::string& path) override {
        auto child = std::make_shared<OpenProxy>(_bus_name, path, _conn);
        return std::static_pointer_cast<Proxy>(child);
    }
};

};  // namespace SimpleDBus
