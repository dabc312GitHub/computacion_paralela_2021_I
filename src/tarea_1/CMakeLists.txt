# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.


#project(tarea_1)
#
#set(CMAKE_CXX_STANDARD)
#
#
## Add tasks subprojects
#include(cmake/utils.cmake)
#add_subprojects(${CMAKE_SOURCE_DIR})


project(tarea_1)

message( "Configuring main application - ${PROJECT_NAME} : " )
message( "\nBuild mode test is: ${CMAKE_BUILD_TYPE}" )
add_executable( ${PROJECT_NAME}  main.cpp)
