cmake_minimum_required(VERSION 3.16)

project(DAC-Qt_tests)

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory("${CMAKE_SOURCE_DIR}/extern/googletest" "extern/googletest")

add_executable(
        DAC-Qt_tests
        broadcaster-tests.cpp
        labjacksink-tests.cpp
)

target_link_libraries(
        DAC-Qt_tests
        libDAC-Qt
        LabJackM
        GTest::gtest_main
)

gtest_discover_tests(DAC-Qt_tests)
