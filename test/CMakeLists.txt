include(CTest)
enable_testing()

include(../cmake/DownloadProject/DownloadProject.cmake)

download_project(
        PROJ googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG master
        UPDATE_DISCONNECTED 1
)

if("${googletest_SOURCE_DIR}" STREQUAL "")
    message(FATAL_ERROR "CMake unable to download googletest source dir: ${googletest_SOURCE_DIR}")
endif()

if("${googletest_BINARY_DIR}" STREQUAL "")
    message(FATA_ERROR "CMake unable to download googletest binary dir: ${googletest_BINARY_DIR}")
endif()
message(STATUS "Googletest succesfully downloaded! : ${googletest_SOURCE_DIR} ${googletest_BINARY_DIR}")

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

enable_testing()

include_directories(include)

set(SOURCES ../src/ghostscript.cpp ../src/ghostscript_op.cpp ../src/utils.cpp ../src/ghost_error.cpp ../src/glimpse_sensor.cpp)

add_executable(run_tests test.cpp ${SOURCES})
target_link_libraries(run_tests ${REQUIRED_LIBRARIES} gtest gmock)
#add_custom_target(run_tests COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS ghost_test)
