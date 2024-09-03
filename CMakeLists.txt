cmake_minimum_required(VERSION 3.1)

project(Philos2.0 VERSION 1.0 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(SRC main.cpp OptionsParser.cpp )

include_directories( . )
add_executable(philosophers ${SRC})
add_compile_options( -g -std=c++17 )

target_link_libraries(philosophers pthread)
