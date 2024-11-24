########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(cpr_COMPONENT_NAMES "")
if(DEFINED cpr_FIND_DEPENDENCY_NAMES)
  list(APPEND cpr_FIND_DEPENDENCY_NAMES CURL)
  list(REMOVE_DUPLICATES cpr_FIND_DEPENDENCY_NAMES)
else()
  set(cpr_FIND_DEPENDENCY_NAMES CURL)
endif()
set(CURL_FIND_MODE "NO_MODULE")

########### VARIABLES #######################################################################
#############################################################################################
set(cpr_PACKAGE_FOLDER_DEBUG "C:/Users/User/.conan2/p/b/cpr1bff76501d839/p")
set(cpr_BUILD_MODULES_PATHS_DEBUG )


set(cpr_INCLUDE_DIRS_DEBUG )
set(cpr_RES_DIRS_DEBUG )
set(cpr_DEFINITIONS_DEBUG )
set(cpr_SHARED_LINK_FLAGS_DEBUG )
set(cpr_EXE_LINK_FLAGS_DEBUG )
set(cpr_OBJECTS_DEBUG )
set(cpr_COMPILE_DEFINITIONS_DEBUG )
set(cpr_COMPILE_OPTIONS_C_DEBUG )
set(cpr_COMPILE_OPTIONS_CXX_DEBUG )
set(cpr_LIB_DIRS_DEBUG "${cpr_PACKAGE_FOLDER_DEBUG}/lib")
set(cpr_BIN_DIRS_DEBUG )
set(cpr_LIBRARY_TYPE_DEBUG STATIC)
set(cpr_IS_HOST_WINDOWS_DEBUG 1)
set(cpr_LIBS_DEBUG cpr)
set(cpr_SYSTEM_LIBS_DEBUG )
set(cpr_FRAMEWORK_DIRS_DEBUG )
set(cpr_FRAMEWORKS_DEBUG )
set(cpr_BUILD_DIRS_DEBUG )
set(cpr_NO_SONAME_MODE_DEBUG FALSE)


# COMPOUND VARIABLES
set(cpr_COMPILE_OPTIONS_DEBUG
    "$<$<COMPILE_LANGUAGE:CXX>:${cpr_COMPILE_OPTIONS_CXX_DEBUG}>"
    "$<$<COMPILE_LANGUAGE:C>:${cpr_COMPILE_OPTIONS_C_DEBUG}>")
set(cpr_LINKER_FLAGS_DEBUG
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${cpr_SHARED_LINK_FLAGS_DEBUG}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${cpr_SHARED_LINK_FLAGS_DEBUG}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${cpr_EXE_LINK_FLAGS_DEBUG}>")


set(cpr_COMPONENTS_DEBUG )