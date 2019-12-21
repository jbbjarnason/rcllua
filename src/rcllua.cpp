//
// Created by jonb on 18.12.2019.
//

#include "rclcpp/rclcpp.hpp"
#include "sol.hpp"

std::vector<char*> captureArgumentsFromLua(sol::table args) {
    std::vector<std::string> luaArgs;
    args.for_each([&](sol::object const& key, sol::object const& value) {
        auto argument = value.as<std::string>();
        auto keyAsInt = key.as<int>();
        if (keyAsInt == 0)
            argument.replace(argument.find_first_of(".lua"),
                             argument.find_last_of(".lua"),
                             "");

        if (keyAsInt >= 0) luaArgs.insert(luaArgs.begin(), argument);
    });

    std::vector<char*> cstrings;
    cstrings.reserve(luaArgs.size());
    for(auto& s: luaArgs)
        cstrings.push_back(&s[0]);
    return cstrings;
}

using namespace rclcpp;

sol::table open_rcl(sol::this_state L) {
    sol::state_view lua(L);
    sol::table module = lua.create_table();

    auto args = captureArgumentsFromLua(lua["arg"]);
    module.new_usertype<Node>("Node",
            "new", sol::constructors<
                    Node(const std::string&, NodeOptions&),
                    Node(const std::string&, const std::string&, NodeOptions&)>(),
            "get_name", &Node::get_name,
            "get_namespace", &Node::get_namespace,
            "get_logger", &Node::get_logger, // TODO: finish
            "create_callback_group", &Node::create_callback_group, // TODO: finish
            "get_callback_groups", &Node::get_callback_groups, // TODO: finish
            "create_publisher", [lua](Node* node, std::string typeName, std::string topic){
                std::cout << "creating " << typeName << std::endl;
                if (typeName == "Byte") {
                    auto pub = node->create_publisher<std_msgs::msg::Byte>(topic, 10);
//                    lua.new_usertype<rclcpp::Publisher<std_msgs::msg::Byte>>("PublisherBase",
//                            "new", sol::no_constructor,
//                            "_create", [node, topic](){
//                                return node->create_publisher<std_msgs::msg::Byte>(topic, 10);
//                            },
//                            "publish", &rclcpp::Publisher<std_msgs::msg::Byte>::publish);
//                    sol::usertype<rclcpp::PublisherBase> foo = lua.new_usertype<rclcpp::PublisherBase>(pub);
                    return;
                }
//                return node->create_publisher<>();
            }
//            "create_publisher", &Node::create_publisher // TODO: finish
//            "create_subscription", &Node::create_subscription // TODO: finish
// TODO: ... finish interface
                    );


    return module;
}


extern "C" int luaopen_rcllua (lua_State* L) {
    return sol::stack::call_lua(L, 1, open_rcl);
}