#include <simpledbus/base/Connection.h>
#include <simpledbus/base/Message.h>

int main(int argc, char* argv[]) {
    SimpleDBus::Connection conn(SimpleDBus::Connection::BusType::Session);
    conn.init();

    auto msg = SimpleDBus::Message::create_method_call(
        "org.freedesktop.Notifications", "/org/freedesktop/Notifications", "org.freedesktop.Notifications", "Notify");

    // For information on these arguments, have a look at the interface definition.
    msg.append_argument(SimpleDBus::Holder::create_string("SimpleDBUS Example"), "s");
    msg.append_argument(SimpleDBus::Holder::create_uint32(42), "u");
    msg.append_argument(SimpleDBus::Holder::create_string("ubuntu-logo"), "s");
    msg.append_argument(SimpleDBus::Holder::create_string("SimpleDBus Notify Summary"), "s");
    msg.append_argument(SimpleDBus::Holder::create_string("This is a SimpleDBus notification."), "s");
    msg.append_argument(SimpleDBus::Holder::create_array(), "as");
    msg.append_argument(SimpleDBus::Holder::create_dict(), "a{sv}");
    msg.append_argument(SimpleDBus::Holder::create_int32(5000), "i");
    conn.send_with_reply_and_block(msg);

    return 0;
}
