#include <simpledbus/base/Logger.h>
#include <simpledbus/interfaces/Introspectable.h>

#include <iostream>

using namespace SimpleDBus;

Introspectable::Introspectable(std::shared_ptr<Connection> conn, std::string bus_name, std::string path)
    : _conn(conn), _bus_name(bus_name), _path(path), _interface_name("org.freedesktop.DBus.Introspectable") {}

Introspectable::~Introspectable() {}

// Names are made matching the ones from the DBus specification
Holder Introspectable::Introspect() {
    LOG_F(DEBUG, "%s -> Introspect()", _path.c_str());
    Message query_msg = Message::create_method_call(_bus_name, _path, _interface_name, "Introspect");

    Message reply_msg = _conn->send_with_reply_and_block(query_msg);
    Holder result = reply_msg.extract();
    return result;
}
