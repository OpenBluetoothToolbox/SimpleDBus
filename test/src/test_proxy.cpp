#include <gtest/gtest.h>

#include <simpledbus/base/Proxy.h>

using namespace SimpleDBus;

class OpenProxy : public Proxy {
  public:
    OpenProxy(const std::string& bus_name, const std::string& path, std::shared_ptr<SimpleDBus::Connection> conn)
        : Proxy(bus_name, path, conn){};
    ~OpenProxy() {}

    std::map<std::string, std::shared_ptr<Proxy>> children() { return _children; }

    std::shared_ptr<Proxy> create_child(const std::string& path, SimpleDBus::Holder options) override {
        return std::static_pointer_cast<Proxy>(std::make_shared<OpenProxy>(_bus_name, path, _conn));
    }
};

TEST(Proxy, AppendChild) {
    OpenProxy p = OpenProxy("", "/a/b", nullptr);

    p.path_add("/a/b/c", Holder());
    EXPECT_EQ(1, p.children().size());
    EXPECT_EQ(1, p.children().count("/a/b/c"));
    EXPECT_EQ("/a/b/c", p.children().at("/a/b/c")->path());
}

TEST(Proxy, AppendRepeatedChild) {
    // TODO: In the future this test should ensure that the Proxy actually does re-initiallize itself.
    OpenProxy p = OpenProxy("", "/a/b", nullptr);
    p.path_add("/a/b/c", Holder());

    // Attempting to add a child with the same name should be a no-op
    p.path_add("/a/b/c", Holder());
    EXPECT_EQ(1, p.children().size());
}

TEST(Proxy, AppendExtendedChild) {
    OpenProxy p = OpenProxy("", "/", nullptr);
    p.path_add("/a/b/c/d", Holder());

    ASSERT_EQ(1, p.children().size());
    ASSERT_EQ(1, p.children().count("/a"));

    std::shared_ptr<OpenProxy> p_a = std::dynamic_pointer_cast<OpenProxy>(p.children().at("/a"));
    ASSERT_EQ(1, p_a->children().size());
    ASSERT_EQ(1, p_a->children().count("/a/b"));

    std::shared_ptr<OpenProxy> p_a_b = std::dynamic_pointer_cast<OpenProxy>(p_a->children().at("/a/b"));
    ASSERT_EQ(1, p_a_b->children().size());
    ASSERT_EQ(1, p_a_b->children().count("/a/b/c"));

    std::shared_ptr<OpenProxy> p_a_b_c = std::dynamic_pointer_cast<OpenProxy>(p_a_b->children().at("/a/b/c"));
    ASSERT_EQ(1, p_a_b_c->children().size());
    ASSERT_EQ(1, p_a_b_c->children().count("/a/b/c/d"));
}
