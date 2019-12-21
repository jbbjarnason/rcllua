////
//// Created by jonb on 18.12.2019.
////
//
//#include "sol.hpp"
//#include "rcllua.cpp"
//
//int main(int, char*[]) {
//    sol::state lua;
//
//    lua.open_libraries(sol::lib::package, sol::lib::base, sol::lib::os);
//    lua.require("rcllua", sol::c_call<decltype(&open_rcl), &open_rcl>);
//
//    const auto& code = R"(
//print(_VERSION)
//print(rcllua)
//
//node = rcllua.Node:new("foo")
//print("finished")
//
//)";
//
//    auto script_result = lua.safe_script(code, &sol::script_pass_on_error);
//    if (script_result.valid()) {
//        std::cout << "The SO was require'd from successfully!" << std::endl;
//    }
//    else {
//        sol::error err = script_result;
//        std::cout << "Something bad happened: " << err.what() << std::endl;
//    }
////    c_assert(script_result.valid());
////    my_object::test& obj = lua["obj"];
////    c_assert(obj.value == 24);
//
//    return 0;
//}


#include <gtest/gtest.h>
#include <memory>

using namespace std;

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}