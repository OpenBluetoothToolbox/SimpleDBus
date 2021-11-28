#include <simpledbus/advanced/Interface.h>

using namespace SimpleDBus;

Interface::Interface(std::shared_ptr<Connection> conn, const std::string& bus_name, const std::string& path,
                     const std::string& interface_name)
    : BasicInterface(conn, bus_name, path, interface_name), _properties(conn, bus_name, path) {}

Holder Interface::property_get(const std::string& property_name) {
    return _properties.Get(_interface_name, property_name);
}
void Interface::property_set(const std::string& property_name, const Holder& value) {
    _properties.Set(_interface_name, property_name, value);
}
