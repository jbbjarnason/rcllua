//
// Created by jonb on 21.12.2019.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#define private public
#define protected public

#include "rcllua.cpp"

sol::state lua;

class NodeTest : public ::testing::Test {
public:
    ~NodeTest() {
//        lua.reset();
    }
    void SetUp() override {
        lua.open_libraries(sol::lib::package, sol::lib::base, sol::lib::os);
        lua.require("rcllua", sol::c_call<decltype(&open_rcl), &open_rcl>);
    }
    void TearDown() override {
    }
    void runScript(const auto& code);
};

void NodeTest::runScript(const auto &code) {
    auto script_result = lua.safe_script(code, &sol::script_pass_on_error);
    sol::error err = script_result;
    ASSERT_TRUE(script_result.valid()) << "Something bad happened: " << err.what();
}

TEST_F(NodeTest, libLoaded) {
    ASSERT_EQ(lua["rcllua"].get_type(), sol::type::table);
}

TEST_F(NodeTest, nodeCreated) {
    const auto& code = R"( node = rcllua.Node:new("foo") )";
    runScript(code);
    ASSERT_EQ(lua["node"].get_type(), sol::type::userdata);
}

TEST_F(NodeTest, nodeName) {
    const auto& code = R"(
node = rcllua.Node:new("foo")
nodeName = node:get_name()
)";
    runScript(code);
    auto node = lua["node"].get<Node*>();
    auto name = lua["nodeName"].get_or(std::string("uninitialized"));
    ASSERT_EQ(name, std::string(node->get_name()));
}