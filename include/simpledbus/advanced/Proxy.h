#pragma once

#include <simpledbus/advanced/ProxyBase.h>
#include <simpledbus/base/Connection.h>
#include <simpledbus/base/Interface.h>
#include <memory>
#include <string>
#include <vector>

namespace SimpleDBus {

// Forward declarations
class Proxy;

class Proxy : public ProxyBase {
  public:
    Proxy(const std::string& bus_name, const std::string& path, std::shared_ptr<SimpleDBus::Connection> conn);
    ~Proxy();

    std::string path() const;

    void path_add(const std::string& path, SimpleDBus::Holder managed_interfaces);
    bool path_remove(const std::string& path, SimpleDBus::Holder options);
    bool path_prune();

  protected:
    virtual std::shared_ptr<Proxy> create_child(const std::string& path);

    /**
     * @brief Callback for child object creation.
     *
     * @param path
     * @param options
     */
    virtual void on_child_created(const std::string& path, SimpleDBus::Holder options);

    /**
     * @brief Callback for child object destruction.
     *
     * @param path
     * @param options
     */
    virtual void on_child_destroyed(const std::string& path);

    std::map<std::string, std::shared_ptr<Proxy>> _children;
};

}  // namespace SimpleDBus
