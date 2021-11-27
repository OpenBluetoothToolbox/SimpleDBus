#include <simpledbus/base/Interface.h>

using namespace SimpleDBus;

Interface::Interface(std::shared_ptr<Connection> conn, const std::string& bus_name, const std::string& path)
    : _conn(conn), _bus_name(bus_name), _path(path), _loaded(true) {}

void Interface::load(Holder options) { _loaded = true; }

void Interface::unload() { _loaded = false; }

bool Interface::is_loaded() const { return _loaded; }
