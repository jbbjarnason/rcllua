//
// Created by jonb on 18.12.2019.
//

#include "rclcpp/rclcpp.hpp"
#include "sol.hpp"

sol::table open_rcl(sol::this_state L) {
    sol::state_view lua(L);
    sol::table module = lua.create_table();

    return module;
}


extern "C" int luaopen_rcllua (lua_State* L) {
    return sol::stack::call_lua(L, 1, open_rcl);
}