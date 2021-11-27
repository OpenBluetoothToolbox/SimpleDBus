#include "simpledbus/base/InterfaceHolder.h"

using namespace SimpleDBus;

InterfaceHolder::InterfaceHolder(std::shared_ptr<Connection> conn, const std::string& bus_name, const std::string& path)
    : _conn(conn), _bus_name(bus_name), _path(path) {}

std::shared_ptr<Interface> InterfaceHolder::interfaces_create(const std::string& name, SimpleDBus::Holder options) {
    return std::make_unique<Interface>(_conn, _bus_name, _path);
}

size_t InterfaceHolder::interfaces_count() const {
    size_t count = 0;
    for (auto& [iface_name, interface] : _interfaces) {
        if (interface->is_loaded()) {
            count++;
        }
    }
    return count;
}

void InterfaceHolder::interfaces_load(Holder managed_interfaces) {
    auto managed_interface = managed_interfaces.get_dict_string();
    for (auto& [iface_name, options] : managed_interface) {
        // If the interface is already in the map, notify the object that it needs to reset itself.
        if (_interfaces.find(iface_name) != _interfaces.end()) {
            _interfaces[iface_name]->load(options);
        } else {
            _interfaces.emplace(std::make_pair(iface_name, interfaces_create(iface_name, options)));
        }
    }
}

void InterfaceHolder::interfaces_reload(Holder managed_interfaces) {
    for (auto& [iface_name, interface] : _interfaces) {
        interface->unload();
    }

    interfaces_load(managed_interfaces);
}

void InterfaceHolder::interfaces_unload(SimpleDBus::Holder removed_interfaces) {
    for (auto& option : removed_interfaces.get_array()) {
        std::string iface_name = option.get_string();
        if (_interfaces.find(iface_name) != _interfaces.end()) {
            _interfaces[iface_name]->unload();
        }
    }
}

bool InterfaceHolder::interfaces_loaded() const {
    for (auto& [iface_name, interface] : _interfaces) {
        if (interface->is_loaded()) {
            return true;
        }
    }
    return false;
}
