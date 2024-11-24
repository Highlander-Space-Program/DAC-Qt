# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\appDAC-Qt_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\appDAC-Qt_autogen.dir\\ParseCache.txt"
  "appDAC-Qt_autogen"
  )
endif()
