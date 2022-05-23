cmake_minimum_required(VERSION 3.17)
project(data_structure)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR}/include)

MATH(EXPR stack_size "8*1024*1024")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")

add_subdirectory(src)
link_directories(src)

## First Link
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} src)

