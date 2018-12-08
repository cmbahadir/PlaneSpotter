# ------------------------------------------------------------------------------
# Sources
# ------------------------------------------------------------------------------

file(GLOB SOURCES "*.cpp")
add_executable(PlaneSpotter ${SOURCES})
add_library(planeSpotter ${SOURCES})

# ------------------------------------------------------------------------------
# Libraries
# ------------------------------------------------------------------------------
target_link_libraries(PlaneSpotter amqpcpp
                                    pthread
                                    event
                                    dl
                                    boost_system
                                    boost_thread)