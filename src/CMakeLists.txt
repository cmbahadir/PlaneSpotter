# ------------------------------------------------------------------------------
# Sources
# ------------------------------------------------------------------------------

file(GLOB SOURCES "*.cpp")
add_executable(PlaneSpotter ${SOURCES})
add_library(planeSpotter ${SOURCES})

# ------------------------------------------------------------------------------
# Libraries
# ------------------------------------------------------------------------------
target_link_libraries(PlaneSpotter amqpcpp)
target_link_libraries(PlaneSpotter pthread)
target_link_libraries(PlaneSpotter event)