# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.


project(tarea_2)

message( "Configuring main application - ${PROJECT_NAME} : " )
message( "\nBuild mode test is: ${CMAKE_BUILD_TYPE}" )
add_executable( ${PROJECT_NAME}  main.cpp)
