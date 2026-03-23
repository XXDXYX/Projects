# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\appServerClient_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\appServerClient_autogen.dir\\ParseCache.txt"
  "appServerClient_autogen"
  )
endif()
