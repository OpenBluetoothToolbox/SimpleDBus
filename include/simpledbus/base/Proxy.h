#pragma once

#include <simpledbus/base/Connection.h>
#include <memory>
#include <string>
#include <vector>

namespace SimpleDBus {

// Forward declarations
class Proxy;

class Proxy {
  public:
    Proxy(const std::string& bus_name, const std::string& path, std::shared_ptr<SimpleDBus::Connection> conn);
    ~Proxy();

    std::string path() const;
    void path_add(const std::string& path, SimpleDBus::Holder options);
    void path_remove(const std::string& path, SimpleDBus::Holder options);

  protected:

    /**
     * @brief Create a child of the Proxy object.
     *
     * @details The default implementation will return generic proxy object.
     *
     * @param path
     * @param options
     * @return std::shared_ptr<Proxy>
     */
    virtual std::shared_ptr<Proxy> create_child(const std::string& path, SimpleDBus::Holder options);

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





    std::string _bus_name;
    std::string _path;
    std::shared_ptr<SimpleDBus::Connection> _conn;

    std::map<std::string, std::shared_ptr<Proxy>> _children;
};

}  // namespace SimpleDBus
