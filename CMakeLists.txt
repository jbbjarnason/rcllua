cmake_minimum_required(VERSION 3.5)
project(rcllua)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
set(CMAKE_CXX_STANDARD 17)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(Lua REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()

add_library(rcllua SHARED src/rcllua.cpp)
target_include_directories(rcllua PRIVATE include)
target_include_directories(rcllua PUBLIC include/rcllua)

ament_target_dependencies(rcllua rclcpp)
target_link_libraries(rcllua ${LUA_LIBRARIES})
include_directories(rcllua ${LUA_INCLUDE_DIR})

add_executable(rcllua_tests test/rcllua_test.cpp)
target_include_directories(rcllua_tests PRIVATE include)
target_include_directories(rcllua_tests PRIVATE src)
ament_target_dependencies(rcllua_tests rclcpp)
target_link_libraries(rcllua_tests ${LUA_LIBRARIES})
include_directories(rcllua_tests ${LUA_INCLUDE_DIR})
target_link_libraries(rcllua_tests rcllua)


install(TARGETS rcllua
        LIBRARY DESTINATION lib/${PROJECT_NAME})
