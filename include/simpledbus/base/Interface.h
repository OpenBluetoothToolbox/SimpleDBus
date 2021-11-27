#pragma once

#include <simpledbus/base/Connection.h>

#include <memory>
#include <string>

namespace SimpleDBus {

class Interface {
  public:
    Interface(std::shared_ptr<SimpleDBus::Connection> conn, const std::string& bus_name, const std::string& path);

    void load(SimpleDBus::Holder options);
    void unload();
    bool is_loaded() const;

  protected:
    bool _loaded{true};

    std::string _path;
    std::string _bus_name;
    std::shared_ptr<SimpleDBus::Connection> _conn;
};

}  // namespace SimpleDBus
