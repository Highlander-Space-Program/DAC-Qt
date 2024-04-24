cmake_minimum_required(VERSION 3.16)
project(DAC-Qt VERSION 0.1 LANGUAGES CXX)

# if(APPLE)
#   if(NOT DEFINED CMAKE_OSX_SYSROOT)
#     message(FATAL_ERROR "Cannot check SDK version if CMAKE_OSX_SYSROOT"
#       " is not defined."
#     )
#   endif()

#   set(DYLD_LIBRARY_PATH "${DYLD_LIBRARY_PATH}:/usr/local/lib")

#   execute_process(
#     COMMAND xcrun --sdk "${CMAKE_OSX_SYSROOT}" --show-sdk-version
#     OUTPUT_VARIABLE sdk_version
#     OUTPUT_STRIP_TRAILING_WHITESPACE
#   )

#   if(CMAKE_SYSTEM_NAME STREQUAL "iOS")
#     if(sdk_version VERSION_LESS 14.2)
#       message(FATAL_ERROR "This project requires at least iPhoneOS SDK"
#         " 14.2, but got ${sdk_version} instead."
#       )
#     endif()
#   else()
#     if(sdk_version VERSION_LESS 11.0)
#       message(FATAL_ERROR "This project requires at least macOS SDK"
#         " 11.0, but got ${sdk_version} instead."
#       )
#     endif()
#   endif()
# endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}")

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")



message(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")

# if(NOT EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
#   execute_process(COMMAND conan install ${CMAKE_BINARY_DIR} --build=missing -s build_type=Release
#                   WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
# endif()

add_definitions(-DSPDLOG_FMT_EXTERNAL=1)

include(${CMAKE_BINARY_DIR}/conan-dependencies/conan_toolchain.cmake)
message(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")

message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message(STATUS "CMAKE_PROGRAM_PATH: ${CMAKE_PROGRAM_PATH}")
message(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
message(STATUS "CMAKE_INCLUDE_PATH: ${CMAKE_INCLUDE_PATH}")
message(STATUS "CMAKE_LIBRARY_PATH: ${CMAKE_LIBRARY_PATH}")
include_directories(${CMAKE_INCLUDE_PATH})

list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}")
# list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}/generators")

# Include the conan toolchain file
find_package(Qt6 6.6.2 COMPONENTS Core Widgets Charts Quick REQUIRED)
find_package(spdlog REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(Boost REQUIRED COMPONENTS system filesystem)
find_package(InfluxDB REQUIRED)

# Setup Qt project
qt_standard_project_setup()
qt_policy(SET QTP0001 NEW)

if(NOT TARGET Boost::Boost AND TARGET Boost::boost)
  add_library(Boost::Boost INTERFACE IMPORTED)
  set_property(TARGET Boost::Boost PROPERTY INTERFACE_LINK_LIBRARIES Boost::boost)
endif()

# Setup Qt project
qt_standard_project_setup()
qt_policy(SET QTP0001 NEW)

# Define library target if tests are enabled
option(PACKAGE_TESTS "Build with Tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    include(GoogleTest)
    # add_subdirectory(test)
    add_library(libDAC-Qt
        models/ForceData.h
        models/PressureData.h
        models/TelemetryData.h
        models/TemperatureData.h
        sinks/LabJackSink.h
        sinks/LabJackSink.cpp sinks/LabJackSinkStrategy.h
        broadcast/Sink.h
        broadcast/Broadcaster.h
    )
endif()

# Define executable target
qt_add_executable(appDAC-Qt
    MANUAL_FINALIZATION
    main.cpp
    # Add other source files as needed
)

# Platform-specific configurations
if(WIN32)
    target_include_directories(appDAC-Qt PRIVATE "C:/Program Files (x86)/LabJack/Drivers")
    target_include_directories(libDAC-Qt PRIVATE "C:/Program Files (x86)/LabJack/Drivers")
    target_link_libraries(appDAC-Qt PRIVATE "C:/Program Files (x86)/LabJack/Drivers/64bit/LabJackM.lib")
    target_link_libraries(libDAC-Qt PRIVATE "C:/Program Files (x86)/LabJack/Drivers/64bit/LabJackM.lib")
    message (STATUS "Including: LabJack/Drivers and LabJackM.lib on Windows")
    if(MSVC)
        target_compile_options(appDAC-Qt PRIVATE "/Zc:__cplusplus" "/permissive-")
        target_compile_options(libDAC-Qt PRIVATE "/Zc:__cplusplus" "/permissive-")
    endif()
else()
    set(CMAKE_MACOSX_RPATH 1)
    set(CMAKE_INSTALL_RPATH "/usr/local/lib")

    list(APPEND CMAKE_PREFIX_PATH /opt/homebrew /usr/local)

    find_path(LabJackM_INCLUDE_DIR NAMES LabJackM.h)
    find_library(LabJackM_LIBRARY NAMES LabJackM-1.23.1 PATHS "/usr/local/lib")
    find_library(LibUSB_LIBRARY NAMES usb-1.0.0 PATHS "/usr/local/lib")

    message(STATUS "LabJackM_LIBRARY: ${LabJackM_LIBRARY}")
    message(STATUS "LabJackM_INCLUDE_DIR: ${LabJackM_INCLUDE_DIR}")
    message(STATUS "LibUSB_LIBRARY: ${LibUSB_LIBRARY}")

    # Assuming you have a target named 'your_target'
    # Replace 'your_target' with the actual target name
    if(LabJackM_LIBRARY AND LabJackM_INCLUDE_DIR AND LibUSB_LIBRARY)
        target_include_directories(appDAC-Qt PRIVATE ${LabJackM_INCLUDE_DIR})
        target_link_libraries(appDAC-Qt PRIVATE ${LabJackM_LIBRARY})
        target_link_libraries(appDAC-Qt PRIVATE ${LibUSB_LIBRARY})
        target_include_directories(libDAC-Qt PRIVATE ${LabJackM_INCLUDE_DIR})
        target_link_libraries(libDAC-Qt PRIVATE ${LabJackM_LIBRARY})
        target_link_libraries(libDAC-Qt PRIVATE ${LibUSB_LIBRARY})
    else()
        message(FATAL_ERROR "LabJackM library not found")
    endif()

    # For CURL, using find_package is more portable if available
    find_package(CURL REQUIRED)
    if(CURL_FOUND)
        target_include_directories(appDAC-Qt PRIVATE ${CURL_INCLUDE_DIRS})
        target_link_libraries(appDAC-Qt PRIVATE ${CURL_LIBRARIES})
        target_include_directories(libDAC-Qt PRIVATE ${CURL_INCLUDE_DIRS})
        target_link_libraries(libDAC-Qt PRIVATE ${CURL_LIBRARIES})
    else()
        message(FATAL_ERROR "CURL not found")
    endif()
endif()

# Define QML module
qt_add_qml_module(appDAC-Qt
    URI DAC-Qt
    VERSION 1.0
    QML_FILES 
        Main.qml 
        Visualization.qml 
        Settings.qml 
        Navigation.qml 
        Setup.qml 
        components/visualization/MockChart.qml
        components/navigation/NavButton.qml
    SOURCES 
        Config.h 
        models/ForceData.h 
        models/PressureData.h 
        models/TelemetryData.h 
        models/TemperatureData.h
        sinks/LabJackSink.h 
        sinks/LabJackSink.cpp 
        sinks/LabJackSinkStrategy.h
        broadcast/Sink.h 
        broadcast/Broadcaster.h 
        launchinhibitor.h 
        launchinhibitor.cpp
)

# Common link libraries
target_link_libraries(appDAC-Qt
    PRIVATE 
    Qt6::Core 
    Qt6::Widgets 
    Qt6::Charts 
    Qt6::Quick 
    spdlog::spdlog 
    InfluxData::InfluxDB
    nlohmann_json::nlohmann_json
)

target_link_libraries(libDAC-Qt
    PRIVATE 
    Qt6::Core 
    Qt6::Widgets 
    Qt6::Charts 
    Qt6::Quick 
    spdlog::spdlog 
    InfluxData::InfluxDB
    nlohmann_json::nlohmann_json
)

# Conditionally link LabJackM library for non-Windows platforms
# if(NOT WIN32)
#     target_link_libraries(appDAC-Qt PRIVATE ${LabJackM_LIBRARY})
#     if(PACKAGE_TESTS)
#         target_link_libraries(libDAC-Qt PRIVATE ${LabJackM_LIBRARY})
#     endif()
# endif()

# Setup target properties for macOS and Windows
set_target_properties(appDAC-Qt PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

# Configure file copying and installation paths
configure_file("config.json" "${CMAKE_CURRENT_BINARY_DIR}/config.json" COPYONLY)
include(GNUInstallDirs)
install(TARGETS appDAC-Qt
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)