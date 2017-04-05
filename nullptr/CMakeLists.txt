cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 14)
project(nullptr)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
