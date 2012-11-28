cmake_minimum_required(VERSION 2.6)

# Questions? Look here:
# http://developer.qt.nokia.com/quarterly/view/using_cmake_to_build_qt_projects

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


project(qt)

find_package(QT4 REQUIRED)
if (QT_FOUND)
    include(${QT_USE_FILE})
else (QT_FOUND)
    message("FATAL ERROR: Qt4 not found.")
endif (QT_FOUND)

include_directories(
    ./
    ../
    /usr/local/include
    /opt/local/include
    /System/Library/Frameworks
    ${CMAKE_CURRENT_BINARY_DIR}
)
link_directories(
    /usr/local/lib
    /opt/local/lib
)

find_library(GL_LIBRARY OpenGL)
find_library(GLUT_LIBRARY GLUT)
set(EXTRA_LIBS ${GL_LIBRARY} ${GLUT_LIBRARY})

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif (NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_FLAGS "-Qunused-arguments -std=c++11 -stdlib=libc++ -Wall -Wno-long-long -pedantic")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2 -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0 -g")

if (CMAKE_BUILD_TYPE MATCHES "Release")
    add_definitions(-DNDEBUG)
endif (CMAKE_BUILD_TYPE MATCHES "Release")

set(SOURCES
    main.cpp
    MainWindow.cpp
    GlWidget.cpp
)

set(HEADERS
    MainWindow.h
    GlWidget.h
)
set(FORMS MainWindow.ui)
#set(RESOURCES images.qrc)

#set(LIBS boost_program_options-mt BulletDynamics BulletCollision LinearMath)

set(QT_USE_QTOPENGL TRUE)
QT4_WRAP_CPP(HEADERS_MOC ${HEADERS})
QT4_WRAP_UI(FORMS_HEADERS ${FORMS})
QT4_ADD_RESOURCES(RESOURCES_RCC ${RESOURCES})

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS} -DPCUBE -DQTVIEWER)

add_executable(qt ${SOURCES} 
    ${HEADERS_MOC}
    ${FORMS_HEADERS}
    ${RESOURCES_RCC}
)
target_link_libraries(qt ${LIBS} ${EXTRA_LIBS} ${QT_LIBRARIES})

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

