# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\appGuestClient_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\appGuestClient_autogen.dir\\ParseCache.txt"
  "appGuestClient_autogen"
  )
endif()
