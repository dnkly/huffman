cmake_minimum_required(VERSION 3.25)

project(huffman LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-Wall -Wextra -O3)

find_package(Boost 1.78 COMPONENTS program_options REQUIRED)

add_executable(
  huffman
  src/main.cpp
  src/huffman.cpp
  src/hufftree.cpp
)

target_link_libraries(huffman Boost::program_options)
