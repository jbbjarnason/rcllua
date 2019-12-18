//
// Created by jonb on 18.12.2019.
//

#include "sol.hpp"

int main(int, char*[]) {
    sol::state lua;

    lua.open_libraries(sol::lib::package, sol::lib::base);
    const auto& code = R"(
require("lfs")

  function attrdir (path)
      for file in lfs.dir(path) do
          if file ~= "." and file ~= ".." then
              local f = path..'/'..file
              print ("\t "..f)
              local attr = lfs.attributes (f)
              assert (type(attr) == "table")
              if attr.mode == "directory" then
                    --attrdir (f)
              else
                  for name, value in pairs(attr) do
                      print (name, value)
                  end
              end
          end
      end
  end

  attrdir(".")
rcllua = require("../librcllua")
node = rcllua.Node("foo")
print("finished"))";

    auto script_result = lua.safe_script(code, &sol::script_pass_on_error);
    if (script_result.valid()) {
        std::cout << "The SO was require'd from successfully!" << std::endl;
    }
    else {
        sol::error err = script_result;
        std::cout << "Something bad happened: " << err.what() << std::endl;
    }
//    c_assert(script_result.valid());
//    my_object::test& obj = lua["obj"];
//    c_assert(obj.value == 24);

    return 0;
}