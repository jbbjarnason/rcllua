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
                    Node(const std::string&, const std::string&, NodeOptions&)>()
                    );


    return module;
}


extern "C" int luaopen_rcllua (lua_State* L) {
    return sol::stack::call_lua(L, 1, open_rcl);
}