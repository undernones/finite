cmake_minimum_required(VERSION 2.6)

#
# If the user specifies -DCMAKE_BUILD_TYPE on the command line, take their
# definition and dump it in the cache along with proper documentation.
# Otherwise set CMAKE_BUILD_TYPE to Debug prior to calling PROJECT().
#
IF(DEFINED CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose the build type.  Options are: Debug, Release")
ELSE(DEFINED CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the build type.  Options are: Debug, Release")
ENDIF(DEFINED CMAKE_BUILD_TYPE)


project(finite)

include_directories(
    ./
    /opt/local/include/eigen3/Eigen
    /opt/local/include
    /usr/local/include
)
link_directories(
    /opt/local/lib
    /usr/local/lib
)

if(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_FLAGS "-Qunused-arguments -std=c++11 -stdlib=libc++ -Wall -Wno-long-long -pedantic")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2 -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0 -g")

IF(CMAKE_BUILD_TYPE MATCHES "Release")
    add_definitions(-DNDEBUG)
ENDIF(CMAKE_BUILD_TYPE MATCHES "Release")

set(CORE_SRC
    Utils.cpp
    Mesh.cpp
    MeshLoader.cpp
    Options.cpp
    Tetrahedron.cpp
    Timing.cpp
    Vertex.cpp
    World.cpp
)
set(LIBS gflags)

IF(APPLE)
    include_directories(/System/Library/Frameworks)
    find_library(GL_LIBRARY OpenGL)
    find_library(GLUT_LIBRARY GLUT)
    set(EXTRA_LIBS ${GL_LIBRARY} ${GLUT_LIBRARY})

#add_subdirectory(viewer)

ENDIF(APPLE)

#add_library(spline ${SPLINE_SRC})
#target_link_libraries(spline ${LIBS} ${EXTRA_LIBS})
add_executable(headless main.cpp ${CORE_SRC})
target_link_libraries(headless ${LIBS})
add_executable(gui gui.cpp ${CORE_SRC})
target_link_libraries(gui ${LIBS} ${EXTRA_LIBS})


MESSAGE(STATUS)
MESSAGE(STATUS "--------------------------------------------------------------------------------")
MESSAGE(STATUS "Change a value with: cmake . -D<Variable>=<Value>")
MESSAGE(STATUS "Example: cmake . -DCMAKE_BUILD_TYPE=Debug")
MESSAGE(STATUS "--------------------------------------------------------------------------------")
MESSAGE(STATUS "CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
IF(CMAKE_BUILD_TYPE MATCHES "Debug")
    MESSAGE(STATUS "Debug compiler flags: ${CMAKE_CXX_FLAGS_DEBUG}")
ELSE(CMAKE_BUILD_TYPE MATCHES "Debug")
    MESSAGE(STATUS "Release compiler flags: ${CMAKE_CXX_FLAGS_RELEASE}")
ENDIF(CMAKE_BUILD_TYPE MATCHES "Debug")
MESSAGE(STATUS "--------------------------------------------------------------------------------")
MESSAGE(STATUS)

