cmake_minimum_required(VERSION 3.16)

project(DAC-Qt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Charts)

qt_standard_project_setup()

qt_add_executable(appDAC-Qt
    main.cpp
    LabJackSink.h
        LabJackSink.cpp
)

qt_add_qml_module(appDAC-Qt
    URI DAC-Qt
    VERSION 1.0
    QML_FILES Main.qml
    QML_FILES Visualization.qml
    QML_FILES Settings.qml
    QML_FILES Pinout.qml
    QML_FILES Navigation.qml
    SOURCES MassData.h PressureData.h TelemetryData.h TemperatureData.h
    SOURCES TelemetryChannel.h
    SOURCES visualizationcontext.h visualizationcontext.cpp
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

target_link_libraries(appDAC-Qt
    PRIVATE Qt6::Quick Qt6::Charts LabJackM
)

include(GNUInstallDirs)
install(TARGETS appDAC-Qt
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
