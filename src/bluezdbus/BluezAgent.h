#pragma once

#include "simpledbus/SimpleDBus.h"

#include <string>

class BluezAgent {
  private:
    SimpleDBus::Connection* _conn;
    std::string _path;

  public:
    BluezAgent(SimpleDBus::Connection* conn, std::string path, SimpleDBus::Holder options);
    ~BluezAgent();

    bool process_received_signal(SimpleDBus::Message& message);

    void RegisterAgent(std::string agent, std::string capability);
    void UnregisterAgent(std::string agent);

};
