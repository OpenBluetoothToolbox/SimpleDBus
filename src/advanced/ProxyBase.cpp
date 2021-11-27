#include "simpledbus/advanced/ProxyBase.h"

using namespace SimpleDBus;

ProxyBase::ProxyBase(std::shared_ptr<Connection> conn, const std::string& bus_name, const std::string& path)
    : _conn(conn), _bus_name(bus_name), _path(path) {}

std::shared_ptr<Interface> ProxyBase::interfaces_create(const std::string& name, SimpleDBus::Holder options) {
    return std::make_unique<Interface>(_conn, _bus_name, _path);
}

// ----- INTERFACE HANDING -----

size_t ProxyBase::interfaces_count() const {
    size_t count = 0;
    for (auto& [iface_name, interface] : _interfaces) {
        if (interface->is_loaded()) {
            count++;
        }
    }
    return count;
}

void ProxyBase::interfaces_load(Holder managed_interfaces) {
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

void ProxyBase::interfaces_reload(Holder managed_interfaces) {
    for (auto& [iface_name, interface] : _interfaces) {
        interface->unload();
    }

    interfaces_load(managed_interfaces);
}

void ProxyBase::interfaces_unload(SimpleDBus::Holder removed_interfaces) {
    for (auto& option : removed_interfaces.get_array()) {
        std::string iface_name = option.get_string();
        if (_interfaces.find(iface_name) != _interfaces.end()) {
            _interfaces[iface_name]->unload();
        }
    }
}

bool ProxyBase::interfaces_loaded() const {
    for (auto& [iface_name, interface] : _interfaces) {
        if (interface->is_loaded()) {
            return true;
        }
    }
    return false;
}
