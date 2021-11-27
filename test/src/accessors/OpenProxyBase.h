#pragma once

#include <simpledbus/advanced/ProxyBase.h>

namespace SimpleDBus {

class OpenProxyBase : public ProxyBase {
  public:
    OpenProxyBase(std::shared_ptr<SimpleDBus::Connection> conn, const std::string& bus_name,
                        const std::string& path)
        : ProxyBase(conn, bus_name, path) {}

    const std::map<std::string, std::shared_ptr<Interface>>& interfaces() { return _interfaces; };
};

};  // namespace SimpleDBus
