cmake_minimum_required(VERSION 3.6)
project(PlaneSpotter C CXX)

include(ExternalProject)
find_package(Git REQUIRED)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ------------------------------------------------------------------------------
# Includes
# ------------------------------------------------------------------------------

include_directories(inc)
include_directories(SYSTEM ${CMAKE_BINARY_DIR}/inc)


# ------------------------------------------------------------------------------
# Copernica AMQP-CPP
# ------------------------------------------------------------------------------

list(APPEND AMQPCPP_CMAKE_ARGUMENTS
    "-DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}"
    "-DAMQP-CPP_BUILD_EXAMPLES=OFF"
    "-DAMQP-CPP_LINUX_TCP=ON"
    "-DAMQP-CPP_BUILD_SHARED=OFF" 
    "-DCMAKE_BUILD_TYPE:STRING=RELEASE"
)

ExternalProject_Add(
    AMQP-CPP
    GIT_REPOSITORY      https://github.com/CopernicaMarketingSoftware/AMQP-CPP.git
    GIT_TAG             v4.0.1
    GIT_SHALLOW         1
    CMAKE_ARGS          ${AMQPCPP_CMAKE_ARGUMENTS}
    SOURCE_DIR          ${CMAKE_BINARY_DIR}/external/AMQP-CPP/src
    BINARY_DIR          ${CMAKE_BINARY_DIR}/external/AMQP-CPP/build
)

add_executable(PlaneSpotter src/main.cpp)
add_dependencies(PlaneSpotter AMQP-CPP)
target_link_libraries(PlaneSpotter )
target_compile_definitions(PlaneSpotter PRIVATE VIRTUAL= MAIN=main)
