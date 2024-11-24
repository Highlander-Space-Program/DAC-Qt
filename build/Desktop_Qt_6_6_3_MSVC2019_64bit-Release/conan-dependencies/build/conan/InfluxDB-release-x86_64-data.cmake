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
set(influxdb-cxx_PACKAGE_FOLDER_RELEASE "C:/Users/User/.conan2/p/b/influ6ffe5227c365a/p")
set(influxdb-cxx_BUILD_MODULES_PATHS_RELEASE )


set(influxdb-cxx_INCLUDE_DIRS_RELEASE "${influxdb-cxx_PACKAGE_FOLDER_RELEASE}/include")
set(influxdb-cxx_RES_DIRS_RELEASE )
set(influxdb-cxx_DEFINITIONS_RELEASE )
set(influxdb-cxx_SHARED_LINK_FLAGS_RELEASE )
set(influxdb-cxx_EXE_LINK_FLAGS_RELEASE )
set(influxdb-cxx_OBJECTS_RELEASE )
set(influxdb-cxx_COMPILE_DEFINITIONS_RELEASE )
set(influxdb-cxx_COMPILE_OPTIONS_C_RELEASE )
set(influxdb-cxx_COMPILE_OPTIONS_CXX_RELEASE )
set(influxdb-cxx_LIB_DIRS_RELEASE "${influxdb-cxx_PACKAGE_FOLDER_RELEASE}/lib")
set(influxdb-cxx_BIN_DIRS_RELEASE )
set(influxdb-cxx_LIBRARY_TYPE_RELEASE STATIC)
set(influxdb-cxx_IS_HOST_WINDOWS_RELEASE 1)
set(influxdb-cxx_LIBS_RELEASE InfluxDB)
set(influxdb-cxx_SYSTEM_LIBS_RELEASE )
set(influxdb-cxx_FRAMEWORK_DIRS_RELEASE )
set(influxdb-cxx_FRAMEWORKS_RELEASE )
set(influxdb-cxx_BUILD_DIRS_RELEASE )
set(influxdb-cxx_NO_SONAME_MODE_RELEASE FALSE)


# COMPOUND VARIABLES
set(influxdb-cxx_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${influxdb-cxx_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${influxdb-cxx_COMPILE_OPTIONS_C_RELEASE}>")
set(influxdb-cxx_LINKER_FLAGS_RELEASE
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${influxdb-cxx_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${influxdb-cxx_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${influxdb-cxx_EXE_LINK_FLAGS_RELEASE}>")


set(influxdb-cxx_COMPONENTS_RELEASE )