# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\appLdjj_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\appLdjj_autogen.dir\\ParseCache.txt"
  "appLdjj_autogen"
  )
endif()
