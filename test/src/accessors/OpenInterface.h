#pragma once

#include "simpledbus/base/Interface.h"

namespace SimpleDBus {

class OpenInterface : public Interface {
  public:
    OpenInterface(std::shared_ptr<SimpleDBus::Connection> conn, const std::string& bus_name, const std::string& path,
                  int id)
        : Interface(conn, bus_name, path), _id(id) {}

    int _id;
};

}  // namespace SimpleDBus
