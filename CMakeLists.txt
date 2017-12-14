cmake_minimum_required(VERSION 3.9.3)
project (ghost)

# Custom CMAKE scripts
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
include(${CMAKE_SOURCE_DIR}/cmake/Utils/SetBuildType.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/Utils/SetCompilerVersion.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/Utils/Find.cmake)

# Build and compiler types
set_buildtype("Release")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
set_compiler_version()
message(STATUS "Custom compiler flags: ${CMAKE_CXX_FLAGS}")

# Libraries and headers (Tesseract, Ghostscript, libpng and OpenCV)
list(APPEND REQUIRED_LIBRARIES "")
list(APPEND REQUIRED_HEADERS "")

set(GS_LIB "/opt/local/lib")
list(APPEND REQUIRED_LIBRARIES ${GS_LIB}/libgs.9.21.dylib)
find(Tesseract)
list(APPEND REQUIRED_HEADERS "/usr/local/opt/tesseract/include")
list(APPEND REQUIRED_LIBRARIES "/usr/local/opt/tesseract/lib/libtesseract.4.dylib")
set(TESSDATA_DIR "/usr/local/Cellar/tesseract/HEAD-1b4fb3a/share")
find(PNG)
find(OpenCV)

message(STATUS ${REQUIRED_LIBRARIES})
message(STATUS ${REQUIRED_HEADERS})

# Headers
include_directories(include ${REQUIRED_HEADERS})

option(BUILD_TEST "Set ON to build tests" OFF)
option(BUILD_SOURCE "Set ON to build source" ON)

get_directory_property(DIRDEFS DIRECTORY ${CMAKE_SOURCE_DIR} COMPILE_DEFINITIONS)
message(STATUS "Found custom definitions: ${DIRDEFS}")

if(BUILD_TEST)
  add_subdirectory(test)
endif()

if(BUILD_SOURCE)
  add_subdirectory(src)
endif()
