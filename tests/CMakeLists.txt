cmake_minimum_required(VERSION 3.16)

project(DAC-Qt_tests)

add_subdirectory("${CMAKE_SOURCE_DIR}/extern/googletest" "extern/googletest")

add_executable(
        DAC-Qt_tests
        broadcaster-tests.cpp
)

target_link_libraries(
        DAC-Qt_tests
        GTest::gtest_main
)

gtest_discover_tests(DAC-Qt_tests)
