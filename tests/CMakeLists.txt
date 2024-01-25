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

if(WIN32)
    target_include_directories(DAC-Qt_tests PRIVATE "C:/Program Files (x86)/LabJack/Drivers")
    target_link_libraries(DAC-Qt_tests PRIVATE "C:/Program Files (x86)/LabJack/Drivers/64bit/LabJackM.lib")
else()
    target_link_libraries(DAC-Qt_tests PRIVATE LabJackM)
endif()

target_link_libraries(DAC-Qt_tests
        PRIVATE libDAC-Qt GTest::gtest_main
)

gtest_discover_tests(DAC-Qt_tests)
