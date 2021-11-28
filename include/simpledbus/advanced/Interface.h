#pragma once

#include <simpledbus/base/BasicInterface.h>
#include <simpledbus/base/Message.h>
#include <simpledbus/interfaces/Properties.h>

#include <functional>

namespace SimpleDBus {

class Interface : public BasicInterface {
  public:
    Interface(std::shared_ptr<Connection> conn, const std::string& bus_name, const std::string& path,
              const std::string& interface_name);
    virtual ~Interface();

    Holder property_get(const std::string& property_name);
    void property_set(const std::string& property_name, const Holder& value);

    Message create_method_call(const std::string& method_name);

  private:
    Interfaces::Properties _properties;
};

}  // namespace SimpleDBus
