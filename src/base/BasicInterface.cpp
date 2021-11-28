#include <simpledbus/base/BasicInterface.h>

using namespace SimpleDBus;

BasicInterface::BasicInterface(std::shared_ptr<Connection> conn, const std::string& bus_name, const std::string& path,
                     const std::string& interface_name)
    : _conn(conn), _bus_name(bus_name), _path(path), _interface_name(interface_name), _loaded(true) {}

void BasicInterface::load(Holder options) { _loaded = true; }

void BasicInterface::unload() { _loaded = false; }

bool BasicInterface::is_loaded() const { return _loaded; }
