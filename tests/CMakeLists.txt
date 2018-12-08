# ------------------------------------------------------------------------------
# Tests
# ------------------------------------------------------------------------------
file(GLOB TEST_SOURCES "*cpp")
add_executable(PlaneSpotter_Test ${TEST_SOURCES})
target_link_libraries(PlaneSpotter_Test planeSpotter 
                                        gtest 
                                        pthread 
                                        boost_system 
                                        boost_thread)