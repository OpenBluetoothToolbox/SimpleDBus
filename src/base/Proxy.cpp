#include <simpledbus/base/Path.h>
#include <simpledbus/base/Proxy.h>

#include <algorithm>

using namespace SimpleDBus;

Proxy::Proxy(const std::string& bus_name, const std::string& path, std::shared_ptr<SimpleDBus::Connection> conn)
    : _bus_name(bus_name), _path(path), _conn(conn) {}

Proxy::~Proxy() {}

std::string Proxy::path() const { return _path; }

void Proxy::path_add(const std::string& path, SimpleDBus::Holder options) {
    // If the path is not a child of the current path, then we can't add it.
    if (!Path::is_descendant(_path, path)) {
        // TODO: Should an exception be thrown here?
        return;
    }

    // If the path is already in the map, notify the object that it needs to reset itself.
    if (_children.find(path) != _children.end()) {
        _children[path]->reset(options);
        return;
    }

    if (Path::is_child(_path, path)) {
        // If the path is a direct child of the proxy path, create a new proxy for it.
        _children.emplace(std::make_pair(path, create_child(path, options)));
        on_child_created(path, options);
    } else {
        // If the new path is for a descendant of the current proxy, check if there is a child proxy for it.
        auto child = std::find_if(_children.begin(), _children.end(),
                                  [path](const std::pair<std::string, std::shared_ptr<Proxy>>& child_data) -> bool {
                                      return Path::is_descendant(child_data.first, path);
                                  });

        if (child != _children.end()) {
            // If there is a child proxy for the new path, forward it to that child proxy.
            child->second->path_add(path, options);
        } else {
            // If there is no child proxy for the new path, create the child and forward the path to it.
            // ! NOTE: This path should not happen very often, if at all.
            std::string child_path = Path::next_child(_path, path);
            _children.emplace(std::make_pair(child_path, create_child(child_path, options)));
            on_child_created(child_path, options);
            _children.at(child_path)->path_add(path, options);
        }
    }
}

void Proxy::path_remove(const std::string& path, SimpleDBus::Holder options) {
    
}

/* Default implementation of virtual methods. */

std::shared_ptr<Proxy> Proxy::create_child(const std::string& path, SimpleDBus::Holder options) {
    return std::make_shared<Proxy>(_bus_name, path, _conn);
}

void Proxy::reset(SimpleDBus::Holder options) {}

void Proxy::on_child_created(const std::string& path, SimpleDBus::Holder options) {}
