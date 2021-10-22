#include "BluezAgent.h"

#include "simpledbus/base/Logger.h"

BluezAgent::BluezAgent(SimpleDBus::Connection* conn, std::string path, SimpleDBus::Holder options)
    : _path(path), _conn(conn) {
    RegisterAgent(_path, "DisplayYesNo");
}

BluezAgent::~BluezAgent() {}

bool BluezAgent::process_received_signal(SimpleDBus::Message& message) {
    if (message.get_path() == _path) {
        return true;
    }
    return false;
}

void BluezAgent::RegisterAgent(std::string agent, std::string capability) {
    SimpleDBus::Holder arg_agent = SimpleDBus::Holder::create_string(agent.c_str());
    SimpleDBus::Holder arg_capability = SimpleDBus::Holder::create_string(capability.c_str());

    LOG_F(DEBUG, "%s -> RegisterAgent", _path.c_str());

    auto msg = SimpleDBus::Message::create_method_call("org.bluez", _path, "org.bluez.AgentManager1", "RegisterAgent");
    msg.append_argument(arg_agent, "o");
    msg.append_argument(arg_capability, "s");
    _conn->send_with_reply_and_block(msg);
}

void BluezAgent::UnregisterAgent(std::string agent) {
    SimpleDBus::Holder arg_agent = SimpleDBus::Holder::create_string(agent.c_str());

    LOG_F(DEBUG, "%s -> UnregisterAgent", _path.c_str());

    auto msg = SimpleDBus::Message::create_method_call("org.bluez", _path, "org.bluez.AgentManager1", "UnregisterAgent");
    msg.append_argument(arg_agent, "o");
    _conn->send_with_reply_and_block(msg);
}
