# cmake_minimum_required(VERSION 3.16)

# project(DAC-Qt_tests)

# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # Add GoogleTest directly to our build. This defines the gtest and gtest_main targets.
# add_subdirectory("${CMAKE_SOURCE_DIR}/extern/googletest" "extern/googletest")

# add_executable(
#     DAC-Qt_tests
#     broadcaster-tests.cpp
#     labjacksink-tests.cpp
# )

# # Include the GoogleTest headers
# target_include_directories(DAC-Qt_tests PRIVATE "${gtest_SOURCE_DIR}/include" "${gmock_SOURCE_DIR}/include")

# if(WIN32)
#     target_include_directories(DAC-Qt_tests PRIVATE "C:/Program Files (x86)/LabJack/Drivers")
#     target_link_libraries(DAC-Qt_tests PRIVATE "C:/Program Files (x86)/LabJack/Drivers/64bit/LabJackM.lib")
# else()
#   list(APPEND CMAKE_PREFIX_PATH /opt/homebrew /usr/local)

#   find_path(LabJackM_INCLUDE_DIR NAMES LabJackM.h)
#   find_library(LabJackM_LIBRARY NAMES LabJackM LabJackM-1.23.0 PATHS "/usr/local/lib")

#   # Assuming you have a target named 'your_target'
#   # Replace 'your_target' with the actual target name
#   if(LabJackM_LIBRARY AND LabJackM_INCLUDE_DIR)
#     message(STATUS "Testing LabJackM_LIBRARY: ${LabJackM_LIBRARY}")
#     message(STATUS "Testing LabJackM_INCLUDE_DIR: ${LabJackM_INCLUDE_DIR}")

#     target_include_directories(DAC-Qt_tests PRIVATE ${LabJackM_INCLUDE_DIR})
#     target_link_libraries(DAC-Qt_tests PRIVATE ${LabJackM_LIBRARY})
#   else()
#     message(FATAL_ERROR "LabJackM library not found")
#   endif()
# endif()

# # Linking against libDAC-Qt (your project library) and GoogleTest
# target_link_libraries(DAC-Qt_tests
#     PRIVATE libDAC-Qt GTest::gtest_main
# )

# # Discover and run tests
# include(GoogleTest)
# gtest_discover_tests(DAC-Qt_tests)
