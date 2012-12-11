cmake_minimum_required(VERSION 2.8)

#
# If the user specifies -DCMAKE_BUILD_TYPE on the command line, take their
# definition and dump it in the cache along with proper documentation.
# Otherwise set CMAKE_BUILD_TYPE to Debug prior to calling project().
#
if (DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose the build type.  Options are: Debug, Release")
else()
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the build type.  Options are: Debug, Release")
endif()


project(finite)

include_directories(
    .
    lib
    /opt/local/include/eigen3/Eigen
    /opt/local/include
    /usr/local/include
)
link_directories(
    /opt/local/lib
    /usr/local/lib
)

if (NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Qunused-arguments -std=c++11 -stdlib=libc++ -Wall -Wno-long-long -pedantic")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2 -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0 -g")

if (CMAKE_BUILD_TYPE MATCHES "Release")
    add_definitions(-DNDEBUG)
endif ()

set (GEOM_SRC
    lib/geom/Mesh.cpp
    lib/geom/MeshLoader.cpp
    lib/geom/Tetrahedron.cpp
    lib/geom/Vertex.cpp
)
add_library(geom ${GEOM_SRC})
target_link_libraries(geom ${LIBS})

set (CORE_SRC
    Utils.cpp
    Obstacle.cpp
    Options.cpp
    PlaneObstacle.cpp
    Timing.cpp
    World.cpp
)

if (APPLE)
    add_subdirectory(qt)
endif()

add_executable(headless main.cpp ${CORE_SRC})
target_link_libraries(headless geom ${LIBS})


message(STATUS)
message(STATUS "--------------------------------------------------------------------------------")
message(STATUS "Change a value with: cmake . -D<Variable>=<Value>")
message(STATUS "Example: cmake . -DCMAKE_BUILD_TYPE=Debug")
message(STATUS "--------------------------------------------------------------------------------")
message(STATUS "CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    message(STATUS "Debug compiler flags: ${CMAKE_CXX_FLAGS_DEBUG}")
else()
    message(STATUS "Release compiler flags: ${CMAKE_CXX_FLAGS_RELEASE}")
endif()
message(STATUS "--------------------------------------------------------------------------------")
message(STATUS)

