# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "Booking_autogen"
  "CMakeFiles\\Booking_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Booking_autogen.dir\\ParseCache.txt"
  )
endif()
