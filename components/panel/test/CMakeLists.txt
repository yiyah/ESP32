# Simple CMakeLists for building the panel unit test as a native host executable
cmake_minimum_required(VERSION 3.16)
project(panel_test C)

include_directories(../include)
add_executable(test_panel test_main.c ../src/panel.c test_bsp.c test_driver.c)

# No special linking required for these basic tests
