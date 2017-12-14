# Source
set(SOURCES ghostscript.cpp ghostscript_op.cpp utils.cpp ghost_error.cpp glimpse_sensor.cpp)

add_executable(ghost ghost.cpp ${SOURCES})
target_link_libraries(ghost ${REQUIRED_LIBRARIES})
