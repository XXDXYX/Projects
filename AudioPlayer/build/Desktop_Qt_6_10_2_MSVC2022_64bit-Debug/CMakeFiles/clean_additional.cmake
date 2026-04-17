# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\appAudioPlayer_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\appAudioPlayer_autogen.dir\\ParseCache.txt"
  "appAudioPlayer_autogen"
  )
endif()
