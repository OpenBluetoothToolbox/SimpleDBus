#include <gtest/gtest.h>

#include <simpledbus/SimpleDBus.h>

using namespace SimpleDBus;

class MessageTest : public ::testing::Test {
  protected:
    void SetUp() override {
        conn = new Connection(DBUS_BUS_SESSION);
        conn->init();
    }

    void TearDown() override {
        delete conn;
        conn = nullptr;
        //conn->uninit();
    }

    Connection* conn;
};

TEST_F(MessageTest, SendReceiveBooleanTrue) {
    Message msg = Message::create_method_call("simpledbus.tester.python", "/", "simpledbus.tester.message",
                                              "SendReceiveBoolean");

    msg.append_argument(Holder::create_boolean(true), DBUS_TYPE_BOOLEAN_AS_STRING);

    Message reply = conn->send_with_reply_and_block(msg);
    Holder h_reply = reply.extract();

    EXPECT_EQ(h_reply.type(), Holder::Type::BOOLEAN);
    EXPECT_EQ(h_reply.get_boolean(), true);
}

TEST_F(MessageTest, SendReceiveBooleanFalse) {
    Message msg = Message::create_method_call("simpledbus.tester.python", "/", "simpledbus.tester.message",
                                              "SendReceiveBoolean");

    msg.append_argument(Holder::create_boolean(false), DBUS_TYPE_BOOLEAN_AS_STRING);

    Message reply = conn->send_with_reply_and_block(msg);
    Holder h_reply = reply.extract();

    EXPECT_EQ(h_reply.type(), Holder::Type::BOOLEAN);
    EXPECT_EQ(h_reply.get_boolean(), false);
}
