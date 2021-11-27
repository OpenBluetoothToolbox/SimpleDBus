#pragma once

#include <simpledbus/base/Connection.h>
#include <simpledbus/base/Interface.h>
#include <simpledbus/base/InterfaceHolder.h>
#include <memory>
#include <string>
#include <vector>

namespace SimpleDBus {

// Forward declarations
class Proxy;

class Proxy : public InterfaceHolder {
  public:
    Proxy(const std::string& bus_name, const std::string& path, std::shared_ptr<SimpleDBus::Connection> conn);
    ~Proxy();

    std::string path() const;

    void path_add(const std::string& path, SimpleDBus::Holder managed_interfaces);
    bool path_remove(const std::string& path, SimpleDBus::Holder options);
    bool path_prune();

    virtual std::shared_ptr<SimpleDBus::Interface> create_interface(const std::string& name,
                                                                    SimpleDBus::Holder options);

  protected:
    virtual std::shared_ptr<Proxy> create_child(const std::string& path);

    // virtual std::shared_ptr<Proxy> destroy_child(const std::string& path, SimpleDBus::Holder options);

    // virtual std::shared_ptr<Interface> create_interface(const std::string& path, SimpleDBus::Holder options);

    // virtual std::shared_ptr<Proxy> destroy_interface(const std::string& path, SimpleDBus::Holder options);

    /**
     * @brief Reset the Proxy object.
     *
     * @param options
     */
    virtual void reset(SimpleDBus::Holder options);

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

    std::string _bus_name;
    std::string _path;
    std::shared_ptr<SimpleDBus::Connection> _conn;

    std::map<std::string, std::shared_ptr<Proxy>> _children;
};

}  // namespace SimpleDBus
