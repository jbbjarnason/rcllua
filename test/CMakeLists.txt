#project(rcllua_tests)

# Download and unpack googletest at configure time
configure_file(${PROJECT_SOURCE_DIR}/cmake/GoogleTest-CMakeLists.txt.in ${CMAKE_BINARY_DIR}/googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)
add_executable(rcllua_tests node_test.cpp rcllua_test.cpp)
target_include_directories(rcllua_tests PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(rcllua_tests PRIVATE ${PROJECT_SOURCE_DIR}/src)
ament_target_dependencies(rcllua_tests rclcpp std_msgs)
target_link_libraries(rcllua_tests ${LUA_LIBRARIES} gtest_main gmock)
include_directories(rcllua_tests ${LUA_INCLUDE_DIR})
