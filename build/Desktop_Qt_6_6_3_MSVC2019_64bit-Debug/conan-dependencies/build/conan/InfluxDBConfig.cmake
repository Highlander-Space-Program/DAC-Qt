########## MACROS ###########################################################################
#############################################################################################

# Requires CMake > 3.15
if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeDeps' generator only works with CMake >= 3.15")
endif()

if(InfluxDB_FIND_QUIETLY)
    set(InfluxDB_MESSAGE_MODE VERBOSE)
else()
    set(InfluxDB_MESSAGE_MODE STATUS)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/cmakedeps_macros.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/InfluxDBTargets.cmake)
include(CMakeFindDependencyMacro)

check_build_type_defined()

foreach(_DEPENDENCY ${influxdb-cxx_FIND_DEPENDENCY_NAMES} )
    # Check that we have not already called a find_package with the transitive dependency
    if(NOT ${_DEPENDENCY}_FOUND)
        find_dependency(${_DEPENDENCY} REQUIRED ${${_DEPENDENCY}_FIND_MODE})
    endif()
endforeach()

set(InfluxDB_VERSION_STRING "0.7.2")
set(InfluxDB_INCLUDE_DIRS ${influxdb-cxx_INCLUDE_DIRS_DEBUG} )
set(InfluxDB_INCLUDE_DIR ${influxdb-cxx_INCLUDE_DIRS_DEBUG} )
set(InfluxDB_LIBRARIES ${influxdb-cxx_LIBRARIES_DEBUG} )
set(InfluxDB_DEFINITIONS ${influxdb-cxx_DEFINITIONS_DEBUG} )


# Only the last installed configuration BUILD_MODULES are included to avoid the collision
foreach(_BUILD_MODULE ${influxdb-cxx_BUILD_MODULES_PATHS_DEBUG} )
    message(${InfluxDB_MESSAGE_MODE} "Conan: Including build module from '${_BUILD_MODULE}'")
    include(${_BUILD_MODULE})
endforeach()


