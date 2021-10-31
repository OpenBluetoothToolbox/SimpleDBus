#include <simpledbus/base/Connection.h>
#include <simpledbus/base/Exceptions.h>
#include <simpledbus/base/Logger.h>

#include <chrono>
#include <iostream>
#include <thread>

using namespace SimpleDBus;

Connection::Connection(DBusBusType dbus_bus_type) : _dbus_bus_type(dbus_bus_type) {}

Connection::~Connection() {
    if (_initialized) {
        uninit();
    }
}

void Connection::init() {
    if (_initialized) {
        return;
    }

    ::DBusError err;
    dbus_error_init(&err);

    dbus_threads_init_default();
    _conn = dbus_bus_get(_dbus_bus_type, &err);
    if (dbus_error_is_set(&err)) {
        LOG_F(ERROR, "Failed to get the DBus bus. (%s: %s)", err.name, err.message);
        dbus_error_free(&err);
        throw Exception::ConnectionException("Failed to get the DBus bus.");
    }
    _initialized = true;
}

void Connection::uninit() {
    if (!_initialized) {
        return;
    }

    // In order to prevent a crash on any third party environment
    // we need to flush the connection queue.
    SimpleDBus::Message message;
    do {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        read_write();
        message = pop_message();
    } while (message.is_valid());

    dbus_connection_unref(_conn);
    _initialized = false;
}

void Connection::add_match(std::string rule) {
    if (!_initialized) {
        throw Exception::ConnectionException("Connection is not initialized.");
    }

    ::DBusError err;
    dbus_error_init(&err);
    dbus_bus_add_match(_conn, rule.c_str(), &err);
    dbus_connection_flush(_conn);
    if (dbus_error_is_set(&err)) {
        LOG_F(ERROR, "Failed to add match. (%s: %s)", err.name, err.message);
        dbus_error_free(&err);
        throw Exception::ConnectionException("Failed to add match.");
    }
}

void Connection::remove_match(std::string rule) {
    if (!_initialized) {
        throw Exception::ConnectionException("Connection is not initialized.");
    }

    ::DBusError err;
    dbus_error_init(&err);
    dbus_bus_remove_match(_conn, rule.c_str(), &err);
    dbus_connection_flush(_conn);
    if (dbus_error_is_set(&err)) {
        LOG_F(ERROR, "Failed to remove match. (%s: %s)", err.name, err.message);
        dbus_error_free(&err);
        throw Exception::ConnectionException("Failed to remove match.");
    }
}

void Connection::read_write() {
    if (!_initialized) {
        throw Exception::ConnectionException("Connection is not initialized.");
    }

    // Non blocking read of the next available message
    dbus_connection_read_write(_conn, 0);
}

Message Connection::pop_message() {
    if (!_initialized) {
        throw Exception::ConnectionException("Connection is not initialized.");
    }

    DBusMessage* msg = dbus_connection_pop_message(_conn);
    if (msg == nullptr) {
        return Message();
    } else {
        return Message(msg);
    }
}

void Connection::send(Message& msg) {
    if (!_initialized) {
        throw Exception::ConnectionException("Connection is not initialized.");
    }

    uint32_t msg_serial = 0;
    bool success = dbus_connection_send(_conn, msg._msg, &msg_serial);

    if (!success) {
        LOG_F(ERROR, "Message send failed.");
        throw Exception::ConnectionException("Message send failed.");
    }

    dbus_connection_flush(_conn);
}

Message Connection::send_with_reply_and_block(Message& msg) {
    if (!_initialized) {
        throw Exception::ConnectionException("Connection is not initialized.");
    }

    ::DBusError err;
    dbus_error_init(&err);
    DBusMessage* msg_tmp = dbus_connection_send_with_reply_and_block(_conn, msg._msg, -1, &err);

    if (dbus_error_is_set(&err)) {
        LOG_F(WARN, "Message send failed. (%s: %s)", err.name, err.message);
        dbus_error_free(&err);
        throw Exception::ConnectionException("Message send failed.");
    }

    return Message(msg_tmp);
}
