cmake_minimum_required(VERSION 3.25)
project(thisisaterminal)

set(CMAKE_CXX_STANDARD 20)

add_executable(thisisaterminal theshell/main.cpp theshell/commands.cpp)
target_include_directories(thisisaterminal PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/theshell)
target_link_libraries(thisisaterminal replxx)

add_executable(command_tests tests/test_commands.cpp)
target_include_directories(command_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/theshell)
target_link_libraries(command_tests gtest gtest_main)

# Google Test stuff
add_subdirectory(googletest)
target_link_libraries(command_tests gtest gtest_main)

# Replxx stuff
set(Replxx_DIR "${CMAKE_CURRENT_SOURCE_DIR}/replxx")
add_subdirectory(${Replxx_DIR})