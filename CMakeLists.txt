cmake_minimum_required(VERSION 3.5)

project(callConstructor)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --save-temps")

aux_source_directory(./src sourceFiles)

add_executable(${PROJECT_NAME} ${sourceFiles})