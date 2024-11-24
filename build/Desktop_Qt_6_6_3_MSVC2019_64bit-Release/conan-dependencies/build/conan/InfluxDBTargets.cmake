# Load the debug and release variables
file(GLOB DATA_FILES "${CMAKE_CURRENT_LIST_DIR}/InfluxDB-*-data.cmake")

foreach(f ${DATA_FILES})
    include(${f})
endforeach()

# Create the targets for all the components
foreach(_COMPONENT ${influxdb-cxx_COMPONENT_NAMES} )
    if(NOT TARGET ${_COMPONENT})
        add_library(${_COMPONENT} INTERFACE IMPORTED)
        message(${InfluxDB_MESSAGE_MODE} "Conan: Component target declared '${_COMPONENT}'")
    endif()
endforeach()

if(NOT TARGET InfluxData::InfluxDB)
    add_library(InfluxData::InfluxDB INTERFACE IMPORTED)
    message(${InfluxDB_MESSAGE_MODE} "Conan: Target declared 'InfluxData::InfluxDB'")
endif()
# Load the debug and release library finders
file(GLOB CONFIG_FILES "${CMAKE_CURRENT_LIST_DIR}/InfluxDB-Target-*.cmake")

foreach(f ${CONFIG_FILES})
    include(${f})
endforeach()