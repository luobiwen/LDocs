# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\mainw_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\mainw_autogen.dir\\ParseCache.txt"
  "mainw_autogen"
  )
endif()
