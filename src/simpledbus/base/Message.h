#pragma once

#include <dbus/dbus.h>

#include <stack>
#include <string>
#include <vector>

#include "Connection.h"
#include "Holder.h"

namespace SimpleDBus {

class Connection;
class Interface;

typedef enum {
    INVALID = DBUS_MESSAGE_TYPE_INVALID,
    METHOD_CALL = DBUS_MESSAGE_TYPE_METHOD_CALL,
    METHOD_RETURN = DBUS_MESSAGE_TYPE_METHOD_RETURN,
    ERROR = DBUS_MESSAGE_TYPE_ERROR,
    SIGNAL = DBUS_MESSAGE_TYPE_SIGNAL,
} MessageType;

class Message {
  private:
    friend class Connection;

    static int creation_counter;
    int indent;

    int _unique_id;
    DBusMessageIter _iter;
    bool _iter_initialized;
    bool _is_extracted;
    Holder _extracted;
    DBusConnection* _borrowed_from;
    DBusMessage* _msg;

    Holder _extract_bytearray(DBusMessageIter* iter);
    Holder _extract_array(DBusMessageIter* iter);
    Holder _extract_dict(DBusMessageIter* iter);
    Holder _extract_generic(DBusMessageIter* iter);
    void _append_argument(DBusMessageIter* iter, Holder& argument, std::string signature);

    void _invalidate();
    void _safe_delete();

  public:
    Message();
    Message(DBusMessage* msg, DBusConnection* borrowed_from = nullptr);
    Message(Message&& other) = delete;         // Remove the move constructor
    Message(const Message& other) = delete;    // Remove the copy constructor
    Message& operator=(Message&& other);       // Implement custom move assignment
    Message& operator=(const Message& other);  // Implement custom copy assignment
    ~Message();

    bool is_valid() const;
    void release();
    void append_argument(Holder argument, std::string signature);
    
    bool is_borrowed() const;
    void steal_if_borrowed();
    void copy_if_borrowed();

    Holder extract();
    void extract_reset();
    bool extract_has_next();
    void extract_next();
    std::string to_string() const;

    std::string get_signature();
    std::string get_interface();
    std::string get_path();
    MessageType get_type();

    bool is_signal(std::string interface, std::string signal_name);

    static Message create_method_call(std::string bus_name, std::string path, std::string interface,
                                      std::string method);
};

}  // namespace SimpleDBus
