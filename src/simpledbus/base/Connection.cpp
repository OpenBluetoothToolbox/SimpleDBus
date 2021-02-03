#include "Connection.h"
#include "simpledbus/base/Logger.h"

#include <chrono>
#include <iostream>
#include <thread>

using namespace SimpleDBus;

Connection::Connection(DBusBusType dbus_bus_type) : _dbus_bus_type(dbus_bus_type) {}

Connection::~Connection() {
    // In order to prevent a crash on any third party environment
    // we need to flush the connection queue.
    SimpleDBus::Message message;
    do {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        read_write();
        message = pop_message();
    } while (message.is_valid());
    // ---------------------------------------------------------

    dbus_error_free(&err);
    dbus_connection_unref(conn);
}

void Connection::init() {
    dbus_threads_init_default();
    dbus_error_init(&err);
    conn = dbus_bus_get(_dbus_bus_type, &err);
    if (dbus_error_is_set(&err)) {
        LOG_F(ERROR, "Failed to get the DBus bus. (%s: %s)", err.name, err.message);
        dbus_error_free(&err);
    }
}

void Connection::add_match(std::string rule) {
    dbus_bus_add_match(conn, rule.c_str(), &err);
    dbus_connection_flush(conn);
    if (dbus_error_is_set(&err)) {
        LOG_F(ERROR, "Failed to add match. (%s: %s)", err.name, err.message);
        dbus_error_free(&err);
    }
}

void Connection::remove_match(std::string rule) {
    dbus_bus_remove_match(conn, rule.c_str(), &err);
    dbus_connection_flush(conn);
    if (dbus_error_is_set(&err)) {
        LOG_F(ERROR, "Failed to remove match. (%s: %s)", err.name, err.message);
        dbus_error_free(&err);
    }
}

void Connection::read_write() {
    // Non blocking read of the next available message
    dbus_connection_read_write_dispatch(conn, 0);
}

Message Connection::pop_message() {
    DBusMessage* msg = dbus_connection_pop_message(conn);
    if (msg == nullptr) {
        return Message();
    } else {
        return Message(msg);
    }
}

Message Connection::borrow_message() {
    DBusMessage* msg = dbus_connection_borrow_message(conn);
    if (msg == nullptr) {
        return Message();
    } else {
        return Message(msg, conn);
    }
}

uint32_t Connection::send(Message& msg) {
    uint32_t msg_serial = 0;
    bool success = dbus_connection_send(conn, msg._msg, &msg_serial);

    if (!success) {
        LOG_F(ERROR, "Message send failed.");
    } else {
        dbus_connection_flush(conn);
    }
    return msg_serial;
}

Message Connection::send_with_reply_and_block(Message& msg) {
    DBusMessage* msg_tmp = dbus_connection_send_with_reply_and_block(conn, msg._msg, -1, &err);

    if (dbus_error_is_set(&err)) {
        LOG_F(WARN, "Message send failed. (%s: %s)", err.name, err.message);
        dbus_error_free(&err);
        return Message(); // TODO: Insert error here into the message class.
    } else {
        return Message(msg_tmp);
    }
}
