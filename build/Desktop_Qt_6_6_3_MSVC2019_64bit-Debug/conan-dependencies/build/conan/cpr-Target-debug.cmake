# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(cpr_FRAMEWORKS_FOUND_DEBUG "") # Will be filled later
conan_find_apple_frameworks(cpr_FRAMEWORKS_FOUND_DEBUG "${cpr_FRAMEWORKS_DEBUG}" "${cpr_FRAMEWORK_DIRS_DEBUG}")

set(cpr_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET cpr_DEPS_TARGET)
    add_library(cpr_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET cpr_DEPS_TARGET
             APPEND PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Debug>:${cpr_FRAMEWORKS_FOUND_DEBUG}>
             $<$<CONFIG:Debug>:${cpr_SYSTEM_LIBS_DEBUG}>
             $<$<CONFIG:Debug>:CURL::libcurl>)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### cpr_DEPS_TARGET to all of them
conan_package_library_targets("${cpr_LIBS_DEBUG}"    # libraries
                              "${cpr_LIB_DIRS_DEBUG}" # package_libdir
                              "${cpr_BIN_DIRS_DEBUG}" # package_bindir
                              "${cpr_LIBRARY_TYPE_DEBUG}"
                              "${cpr_IS_HOST_WINDOWS_DEBUG}"
                              cpr_DEPS_TARGET
                              cpr_LIBRARIES_TARGETS  # out_libraries_targets
                              "_DEBUG"
                              "cpr"    # package_name
                              "${cpr_NO_SONAME_MODE_DEBUG}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${cpr_BUILD_DIRS_DEBUG} ${CMAKE_MODULE_PATH})

########## GLOBAL TARGET PROPERTIES Debug ########################################
    set_property(TARGET cpr::cpr
                 APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                 $<$<CONFIG:Debug>:${cpr_OBJECTS_DEBUG}>
                 $<$<CONFIG:Debug>:${cpr_LIBRARIES_TARGETS}>
                 )

    if("${cpr_LIBS_DEBUG}" STREQUAL "")
        # If the package is not declaring any "cpp_info.libs" the package deps, system libs,
        # frameworks etc are not linked to the imported targets and we need to do it to the
        # global target
        set_property(TARGET cpr::cpr
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     cpr_DEPS_TARGET)
    endif()

    set_property(TARGET cpr::cpr
                 APPEND PROPERTY INTERFACE_LINK_OPTIONS
                 $<$<CONFIG:Debug>:${cpr_LINKER_FLAGS_DEBUG}>)
    set_property(TARGET cpr::cpr
                 APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                 $<$<CONFIG:Debug>:${cpr_INCLUDE_DIRS_DEBUG}>)
    # Necessary to find LINK shared libraries in Linux
    set_property(TARGET cpr::cpr
                 APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                 $<$<CONFIG:Debug>:${cpr_LIB_DIRS_DEBUG}>)
    set_property(TARGET cpr::cpr
                 APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                 $<$<CONFIG:Debug>:${cpr_COMPILE_DEFINITIONS_DEBUG}>)
    set_property(TARGET cpr::cpr
                 APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                 $<$<CONFIG:Debug>:${cpr_COMPILE_OPTIONS_DEBUG}>)

########## For the modules (FindXXX)
set(cpr_LIBRARIES_DEBUG cpr::cpr)
