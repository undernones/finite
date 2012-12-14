cmake_minimum_required(VERSION 2.8)

# Questions? Look here:
# http://developer.qt.nokia.com/quarterly/view/using_cmake_to_build_qt_projects

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


project(qtgui)

find_package(Qt4 REQUIRED)
if (QT_FOUND)
    include(${QT_USE_FILE})
else()
    message("FATAL ERROR: Qt4 not found.")
endif()

include_directories(
    .
    ../lib
    /usr/local/include
    /opt/local/include
    /System/Library/Frameworks
    ${CMAKE_CURRENT_BINARY_DIR}
)
link_directories(
    ..
    /usr/local/lib
    /opt/local/lib
)

find_library(GL_LIBRARY OpenGL)
find_library(GLUT_LIBRARY GLUT)
set(EXTRA_LIBS ${GL_LIBRARY} ${GLUT_LIBRARY})

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_FLAGS "-Qunused-arguments -std=c++11 -stdlib=libc++ -Wall -Wno-long-long -pedantic")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2 -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0 -g")

if (CMAKE_BUILD_TYPE MATCHES "Release")
    add_definitions(-DNDEBUG)
endif()

set(SOURCES
    main.cpp
    GlWidget.cpp
    MainWindow.cpp
    MatrixViewer.cpp
    SimThread.cpp
    ../Obstacle.cpp
    ../Options.cpp
    ../PlaneObstacle.cpp
    ../World.cpp
)
# TODO: ^ Dependencies!

set(FORMS MainWindow.ui MatrixViewer.ui)
set(RESOURCES images.qrc)
set(LIBS geom physics)

set(CMAKE_AUTOMOC ON)
set(QT_USE_QTOPENGL TRUE)
qt4_wrap_ui(FORMS_HEADERS ${FORMS})
qt4_add_resources(RESOURCES_RCC ${RESOURCES})

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS} -DPCUBE -DQTVIEWER)

add_executable(qtgui ${SOURCES} 
    ${FORMS_HEADERS}
    ${RESOURCES_RCC}
)
target_link_libraries(qtgui ${LIBS} ${EXTRA_LIBS} ${QT_LIBRARIES})

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

