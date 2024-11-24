# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(influxdb-cxx_FRAMEWORKS_FOUND_DEBUG "") # Will be filled later
conan_find_apple_frameworks(influxdb-cxx_FRAMEWORKS_FOUND_DEBUG "${influxdb-cxx_FRAMEWORKS_DEBUG}" "${influxdb-cxx_FRAMEWORK_DIRS_DEBUG}")

set(influxdb-cxx_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET influxdb-cxx_DEPS_TARGET)
    add_library(influxdb-cxx_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET influxdb-cxx_DEPS_TARGET
             APPEND PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Debug>:${influxdb-cxx_FRAMEWORKS_FOUND_DEBUG}>
             $<$<CONFIG:Debug>:${influxdb-cxx_SYSTEM_LIBS_DEBUG}>
             $<$<CONFIG:Debug>:cpr::cpr>)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### influxdb-cxx_DEPS_TARGET to all of them
conan_package_library_targets("${influxdb-cxx_LIBS_DEBUG}"    # libraries
                              "${influxdb-cxx_LIB_DIRS_DEBUG}" # package_libdir
                              "${influxdb-cxx_BIN_DIRS_DEBUG}" # package_bindir
                              "${influxdb-cxx_LIBRARY_TYPE_DEBUG}"
                              "${influxdb-cxx_IS_HOST_WINDOWS_DEBUG}"
                              influxdb-cxx_DEPS_TARGET
                              influxdb-cxx_LIBRARIES_TARGETS  # out_libraries_targets
                              "_DEBUG"
                              "influxdb-cxx"    # package_name
                              "${influxdb-cxx_NO_SONAME_MODE_DEBUG}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${influxdb-cxx_BUILD_DIRS_DEBUG} ${CMAKE_MODULE_PATH})

########## GLOBAL TARGET PROPERTIES Debug ########################################
    set_property(TARGET InfluxData::InfluxDB
                 APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                 $<$<CONFIG:Debug>:${influxdb-cxx_OBJECTS_DEBUG}>
                 $<$<CONFIG:Debug>:${influxdb-cxx_LIBRARIES_TARGETS}>
                 )

    if("${influxdb-cxx_LIBS_DEBUG}" STREQUAL "")
        # If the package is not declaring any "cpp_info.libs" the package deps, system libs,
        # frameworks etc are not linked to the imported targets and we need to do it to the
        # global target
        set_property(TARGET InfluxData::InfluxDB
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     influxdb-cxx_DEPS_TARGET)
    endif()

    set_property(TARGET InfluxData::InfluxDB
                 APPEND PROPERTY INTERFACE_LINK_OPTIONS
                 $<$<CONFIG:Debug>:${influxdb-cxx_LINKER_FLAGS_DEBUG}>)
    set_property(TARGET InfluxData::InfluxDB
                 APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                 $<$<CONFIG:Debug>:${influxdb-cxx_INCLUDE_DIRS_DEBUG}>)
    # Necessary to find LINK shared libraries in Linux
    set_property(TARGET InfluxData::InfluxDB
                 APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                 $<$<CONFIG:Debug>:${influxdb-cxx_LIB_DIRS_DEBUG}>)
    set_property(TARGET InfluxData::InfluxDB
                 APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                 $<$<CONFIG:Debug>:${influxdb-cxx_COMPILE_DEFINITIONS_DEBUG}>)
    set_property(TARGET InfluxData::InfluxDB
                 APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                 $<$<CONFIG:Debug>:${influxdb-cxx_COMPILE_OPTIONS_DEBUG}>)

########## For the modules (FindXXX)
set(influxdb-cxx_LIBRARIES_DEBUG InfluxData::InfluxDB)
