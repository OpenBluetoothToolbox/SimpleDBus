#include <simpledbus/base/Path.h>
#include <simpledbus/base/Proxy.h>

#include <algorithm>

#include <iostream>

using namespace SimpleDBus;

Proxy::Proxy(const std::string& bus_name, const std::string& path, std::shared_ptr<SimpleDBus::Connection> conn)
    : InterfaceHolder(conn, bus_name, path), _bus_name(bus_name), _path(path), _conn(conn) {}

Proxy::~Proxy() {}

std::string Proxy::path() const { return _path; }

void Proxy::path_add(const std::string& path, SimpleDBus::Holder managed_interfaces) {
    // If the path is not a child of the current path, then we can't add it.
    if (!Path::is_descendant(_path, path)) {
        // TODO: Should an exception be thrown here?
        return;
    }

    // If the path is already in the map, perform a reload of all interfaces.
    if (_children.find(path) != _children.end()) {
        _children[path]->interfaces_load(managed_interfaces);
        return;
    }

    if (Path::is_child(_path, path)) {
        // If the path is a direct child of the proxy path, create a new proxy for it.
        std::shared_ptr<Proxy> child = create_child(path);
        child->interfaces_load(managed_interfaces);
        _children.emplace(std::make_pair(path, child));
        on_child_created(path, managed_interfaces);
    } else {
        // If the new path is for a descendant of the current proxy, check if there is a child proxy for it.
        auto child_result = std::find_if(
            _children.begin(), _children.end(),
            [path](const std::pair<std::string, std::shared_ptr<Proxy>>& child_data) -> bool {
                return Path::is_descendant(child_data.first, path);
            });

        if (child_result != _children.end()) {
            // If there is a child proxy for the new path, forward it to that child proxy.
            child_result->second->path_add(path, managed_interfaces);
        } else {
            // If there is no child proxy for the new path, create the child and forward the path to it.
            // This path will be taken if an empty proxy object needs to be created for an intermediate path.
            std::string child_path = Path::next_child(_path, path);
            std::shared_ptr<Proxy> child = create_child(child_path);
            on_child_created(child_path, managed_interfaces);
            _children.emplace(std::make_pair(child_path, child));
            child->path_add(path, managed_interfaces);
        }
    }
}

bool Proxy::path_remove(const std::string& path, SimpleDBus::Holder options) {
    // `options` contains an array of strings of the interfaces that need to be removed.

    if (path == _path) {
        interfaces_unload(options);
        return path_prune();
    }

    // If the path is not the current path nor a descendant, then there's nothing to do
    if (!Path::is_descendant(_path, path)) {
        return false;
    }

    // If the path is a direct child of the proxy path, forward the request to the child proxy.
    std::string child_path = Path::next_child(_path, path);
    if (_children.find(child_path) != _children.end()) {
        bool must_erase = _children.at(child_path)->path_remove(path, options);

        // if the child proxy is no longer needed and there is only one active instance of the child proxy,
        // then remove it.
        if (must_erase && _children.at(child_path).use_count() == 1) {
            _children.erase(child_path);
            on_child_destroyed(child_path);
        }
    }

    return false;
}

bool Proxy::path_prune() {
    // For each child proxy, check if it can be pruned.
    std::vector<std::string> to_remove;
    for (auto& [child_path, child] : _children) {
        if (child->path_prune() && _children.at(child_path).use_count() == 1) {
            to_remove.push_back(child_path);
        }
    }
    for (auto& child_path : to_remove) {
        _children.erase(child_path);
        on_child_destroyed(child_path);
    }

    // For self to be pruned, the following conditions must be met:
    // 1. The proxy has no children
    // 2. The proxy has no interfaces or all interfaces are disabled.
    if (_children.empty() && !interfaces_loaded()) {
        return true;
    }

    return false;
}

/* Default implementation of virtual methods. */

std::shared_ptr<Proxy> Proxy::create_child(const std::string& path) {
    return std::make_shared<Proxy>(_bus_name, path, _conn);
}

std::shared_ptr<Interface> Proxy::create_interface(const std::string& name, SimpleDBus::Holder options) {
    return std::make_unique<Interface>(_conn, _bus_name, _path);
}

void Proxy::reset(SimpleDBus::Holder options) {}

/* Default implementation of callbacks */

void Proxy::on_child_created(const std::string& path, SimpleDBus::Holder options) {}

void Proxy::on_child_destroyed(const std::string& path) {}
