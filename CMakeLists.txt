cmake_minimum_required(VERSION 3.16)

project(DAC-Qt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_STANDARD_CXX 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

add_subdirectory(
tests
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

qt_standard_project_setup()

qt_add_executable(appDAC-Qt
    main.cpp
)

qt_add_qml_module(appDAC-Qt
    URI DAC-Qt
    VERSION 1.0
    QML_FILES Main.qml
    SOURCES
    QML_FILES Visualization.qml
    QML_FILES Settings.qml
    QML_FILES Pinout.qml
    QML_FILES Navigation.qml
    SOURCES MassData.h PressureData.h TelemetryDataBase.h TemperatureData.h
    QML_FILES Setup.qml
    SOURCES launchinhibitor.h launchinhibitor.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appDAC-Qt PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appDAC-Qt
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_include_directories(appDAC-Qt PRIVATE "C:/Program Files (x86)/LabJack/Drivers")
target_link_libraries(appDAC-Qt
    PRIVATE Qt6::Quick
    GTest::gtest_main
    PRIVATE "C:/Program Files (x86)/LabJack/Drivers/64bit/LabJackM.lib"
)


include(GNUInstallDirs)
install(TARGETS appDAC-Qt
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

enable_testing()

include(GoogleTest)
