########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(influxdb-cxx_COMPONENT_NAMES "")
if(DEFINED influxdb-cxx_FIND_DEPENDENCY_NAMES)
  list(APPEND influxdb-cxx_FIND_DEPENDENCY_NAMES cpr)
  list(REMOVE_DUPLICATES influxdb-cxx_FIND_DEPENDENCY_NAMES)
else()
  set(influxdb-cxx_FIND_DEPENDENCY_NAMES cpr)
endif()
set(cpr_FIND_MODE "NO_MODULE")

########### VARIABLES #######################################################################
#############################################################################################
set(influxdb-cxx_PACKAGE_FOLDER_DEBUG "C:/Users/User/.conan2/p/b/influ3a20e9ddd5218/p")
set(influxdb-cxx_BUILD_MODULES_PATHS_DEBUG )


set(influxdb-cxx_INCLUDE_DIRS_DEBUG "${influxdb-cxx_PACKAGE_FOLDER_DEBUG}/include")
set(influxdb-cxx_RES_DIRS_DEBUG )
set(influxdb-cxx_DEFINITIONS_DEBUG )
set(influxdb-cxx_SHARED_LINK_FLAGS_DEBUG )
set(influxdb-cxx_EXE_LINK_FLAGS_DEBUG )
set(influxdb-cxx_OBJECTS_DEBUG )
set(influxdb-cxx_COMPILE_DEFINITIONS_DEBUG )
set(influxdb-cxx_COMPILE_OPTIONS_C_DEBUG )
set(influxdb-cxx_COMPILE_OPTIONS_CXX_DEBUG )
set(influxdb-cxx_LIB_DIRS_DEBUG "${influxdb-cxx_PACKAGE_FOLDER_DEBUG}/lib")
set(influxdb-cxx_BIN_DIRS_DEBUG )
set(influxdb-cxx_LIBRARY_TYPE_DEBUG STATIC)
set(influxdb-cxx_IS_HOST_WINDOWS_DEBUG 1)
set(influxdb-cxx_LIBS_DEBUG InfluxDB)
set(influxdb-cxx_SYSTEM_LIBS_DEBUG )
set(influxdb-cxx_FRAMEWORK_DIRS_DEBUG )
set(influxdb-cxx_FRAMEWORKS_DEBUG )
set(influxdb-cxx_BUILD_DIRS_DEBUG )
set(influxdb-cxx_NO_SONAME_MODE_DEBUG FALSE)


# COMPOUND VARIABLES
set(influxdb-cxx_COMPILE_OPTIONS_DEBUG
    "$<$<COMPILE_LANGUAGE:CXX>:${influxdb-cxx_COMPILE_OPTIONS_CXX_DEBUG}>"
    "$<$<COMPILE_LANGUAGE:C>:${influxdb-cxx_COMPILE_OPTIONS_C_DEBUG}>")
set(influxdb-cxx_LINKER_FLAGS_DEBUG
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${influxdb-cxx_SHARED_LINK_FLAGS_DEBUG}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${influxdb-cxx_SHARED_LINK_FLAGS_DEBUG}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${influxdb-cxx_EXE_LINK_FLAGS_DEBUG}>")


set(influxdb-cxx_COMPONENTS_DEBUG )