cmake_minimum_required(VERSION 3.25)
project(monochrome CXX)
set(CMAKE_CXX_STANDARD 23)

include_directories(deps/mono/include)
link_directories(deps/mono/lib)

add_library(monochrome SHARED src/monochrome.cpp)
set_target_properties(monochrome PROPERTIES PUBLIC_HEADER "include/monochrome.h")

target_link_libraries(monochrome mono-2.0-sgen)

