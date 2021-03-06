function(set_compiler_version)
  # Set c++ standard to c++11
  set(CMAKE_CXX_STANDARD 11)
  include(CheckCXXCompilerFlag)
  CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
  CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
  if(COMPILER_SUPPORTS_CXX11)
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} supports C++11.")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" PARENT_SCOPE)
  elseif(COMPILER_SUPPORTS_CXX0X)
    message(WARNING "WARNING: Compiler ${CMAKE_CXX_COMPILER} ONLY supports C++98 .")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x" PARENT_SCOPE)
  else()
    set(ERR_MESSAGE "The compiler ${CMAKE_CXX_COMPILER} has 'NO' C++11 support.")
    set(EX_MESSAGE "Try to use a newer C++ compiler. If there is a C++11 compatible compiler in use, try to specify it.\n Example:\n export CC=/usr/local/bin/gcc \n export CXX=/usr/local/bin/g++ \n")
    message(FATAL_ERROR "${ERR_MESSAGE} ${EX_MESSAGE}")
  endif()
endfunction()
