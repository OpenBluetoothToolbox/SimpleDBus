#include <simpledbus/base/Logger.h>
#include <simpledbus/interfaces/Properties.h>

#include <iostream>

using namespace SimpleDBus;

Properties::Properties(std::shared_ptr<Connection> conn, std::string bus_name, std::string path)
    : Interface(conn, bus_name, path, "org.freedesktop.DBus.Properties") {}

Properties::~Properties() {}

// Names are made matching the ones from the DBus specification
Holder Properties::Get(std::string interface, std::string name) {
    LOG_F(DEBUG, "%s -> Get(%s, %s)", _path.c_str(), interface.c_str(), name.c_str());
    Message query_msg = Message::create_method_call(_bus_name, _path, _interface_name, "Get");

    Holder h_interface = Holder::create_string(interface.c_str());
    query_msg.append_argument(h_interface, "s");

    Holder h_name = Holder::create_string(name.c_str());
    query_msg.append_argument(h_name, "s");

    Message reply_msg = _conn->send_with_reply_and_block(query_msg);
    Holder result = reply_msg.extract();
    return result;
}

Holder Properties::GetAll(std::string interface) {
    LOG_F(DEBUG, "%s -> GetAll(%s)", _path.c_str(), interface.c_str());
    Message query_msg = Message::create_method_call(_bus_name, _path, _interface_name, "GetAll");

    Holder h_interface = Holder::create_string(interface.c_str());
    query_msg.append_argument(h_interface, "s");

    Message reply_msg = _conn->send_with_reply_and_block(query_msg);
    Holder result = reply_msg.extract();
    return result;
}

void Properties::Set(std::string interface, std::string name, Holder value) {
    LOG_F(DEBUG, "%s -> Set(%s, %s, %s)", _path.c_str(), interface.c_str(), name.c_str(), value.represent().c_str());
    Message query_msg = Message::create_method_call(_bus_name, _path, _interface_name, "Set");

    Holder h_interface = Holder::create_string(interface.c_str());
    query_msg.append_argument(h_interface, "s");

    Holder h_name = Holder::create_string(name.c_str());
    query_msg.append_argument(h_name, "s");

    query_msg.append_argument(value, "v");

    _conn->send_with_reply_and_block(query_msg);
}
