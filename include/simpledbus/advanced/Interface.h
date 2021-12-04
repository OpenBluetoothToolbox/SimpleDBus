#pragma once

#include <simpledbus/base/Connection.h>

#include <memory>
#include <string>

namespace SimpleDBus {

class Interface {
  public:
    Interface(std::shared_ptr<Connection> conn, const std::string& bus_name, const std::string& path,
              const std::string& interface_name);

    virtual ~Interface() = default;

    // ----- LIFE CYCLE -----
    void load(Holder options);
    void unload();
    bool is_loaded() const;

    // ----- METHODS -----

    Message create_method_call(const std::string& method_name);

    // ----- PROPERTIES -----
    virtual void property_changed(std::string option_name, Holder value);
    virtual void property_removed(std::string option_name);

    Holder property_get_all();
    Holder property_get(const std::string& property_name);
    void property_set(const std::string& property_name, const Holder& value);

    // ----- SIGNALS -----
    void signal_property_changed(Holder changed_properties, Holder invalidated_properties);

  protected:
    bool _loaded{true};

    std::string _path;
    std::string _bus_name;
    std::string _interface_name;
    std::shared_ptr<Connection> _conn;
};

}  // namespace SimpleDBus
