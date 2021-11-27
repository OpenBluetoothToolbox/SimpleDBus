#pragma once

#include <simpledbus/base/InterfaceHolder.h>

namespace SimpleDBus {

class OpenInterfaceHolder : public InterfaceHolder {
  public:
    OpenInterfaceHolder(std::shared_ptr<SimpleDBus::Connection> conn, const std::string& bus_name,
                        const std::string& path)
        : InterfaceHolder(conn, bus_name, path) {}

    const std::map<std::string, std::shared_ptr<Interface>>& interfaces() { return _interfaces; };
};

};  // namespace SimpleDBus
