function(set_buildtype arg1)
  #####
  # Set the build type to arg1.

  if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "${arg1}")
  else()
    if (NOT CMAKE_BUILD_TYPE STREQUAL "${arg1}")
      message(STATUS "Overwriting build type ${CMAKE_BUILD_TYPE} for build type ${arg1}")
      set(CMAKE_BUILD_TYPE "${arg1}")
    endif()
  endif ()
  message("==========================================================================================")
  message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
  message("==========================================================================================")
endfunction()
