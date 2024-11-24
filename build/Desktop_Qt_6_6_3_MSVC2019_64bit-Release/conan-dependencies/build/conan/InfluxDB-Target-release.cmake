# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(influxdb-cxx_FRAMEWORKS_FOUND_RELEASE "") # Will be filled later
conan_find_apple_frameworks(influxdb-cxx_FRAMEWORKS_FOUND_RELEASE "${influxdb-cxx_FRAMEWORKS_RELEASE}" "${influxdb-cxx_FRAMEWORK_DIRS_RELEASE}")

set(influxdb-cxx_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET influxdb-cxx_DEPS_TARGET)
    add_library(influxdb-cxx_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET influxdb-cxx_DEPS_TARGET
             APPEND PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Release>:${influxdb-cxx_FRAMEWORKS_FOUND_RELEASE}>
             $<$<CONFIG:Release>:${influxdb-cxx_SYSTEM_LIBS_RELEASE}>
             $<$<CONFIG:Release>:cpr::cpr>)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### influxdb-cxx_DEPS_TARGET to all of them
conan_package_library_targets("${influxdb-cxx_LIBS_RELEASE}"    # libraries
                              "${influxdb-cxx_LIB_DIRS_RELEASE}" # package_libdir
                              "${influxdb-cxx_BIN_DIRS_RELEASE}" # package_bindir
                              "${influxdb-cxx_LIBRARY_TYPE_RELEASE}"
                              "${influxdb-cxx_IS_HOST_WINDOWS_RELEASE}"
                              influxdb-cxx_DEPS_TARGET
                              influxdb-cxx_LIBRARIES_TARGETS  # out_libraries_targets
                              "_RELEASE"
                              "influxdb-cxx"    # package_name
                              "${influxdb-cxx_NO_SONAME_MODE_RELEASE}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${influxdb-cxx_BUILD_DIRS_RELEASE} ${CMAKE_MODULE_PATH})

########## GLOBAL TARGET PROPERTIES Release ########################################
    set_property(TARGET InfluxData::InfluxDB
                 APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                 $<$<CONFIG:Release>:${influxdb-cxx_OBJECTS_RELEASE}>
                 $<$<CONFIG:Release>:${influxdb-cxx_LIBRARIES_TARGETS}>
                 )

    if("${influxdb-cxx_LIBS_RELEASE}" STREQUAL "")
        # If the package is not declaring any "cpp_info.libs" the package deps, system libs,
        # frameworks etc are not linked to the imported targets and we need to do it to the
        # global target
        set_property(TARGET InfluxData::InfluxDB
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     influxdb-cxx_DEPS_TARGET)
    endif()

    set_property(TARGET InfluxData::InfluxDB
                 APPEND PROPERTY INTERFACE_LINK_OPTIONS
                 $<$<CONFIG:Release>:${influxdb-cxx_LINKER_FLAGS_RELEASE}>)
    set_property(TARGET InfluxData::InfluxDB
                 APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                 $<$<CONFIG:Release>:${influxdb-cxx_INCLUDE_DIRS_RELEASE}>)
    # Necessary to find LINK shared libraries in Linux
    set_property(TARGET InfluxData::InfluxDB
                 APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                 $<$<CONFIG:Release>:${influxdb-cxx_LIB_DIRS_RELEASE}>)
    set_property(TARGET InfluxData::InfluxDB
                 APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                 $<$<CONFIG:Release>:${influxdb-cxx_COMPILE_DEFINITIONS_RELEASE}>)
    set_property(TARGET InfluxData::InfluxDB
                 APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                 $<$<CONFIG:Release>:${influxdb-cxx_COMPILE_OPTIONS_RELEASE}>)

########## For the modules (FindXXX)
set(influxdb-cxx_LIBRARIES_RELEASE InfluxData::InfluxDB)
