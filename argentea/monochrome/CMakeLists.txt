cmake_minimum_required(VERSION 3.25)
project(monochrome CXX)
set(CMAKE_CXX_STANDARD 23)

include_directories(deps/mono/include)
link_directories(deps/mono/lib)

add_library(monochrome SHARED src/monochrome.cpp src/mono/MonoAssembly.cpp src/mono/MonoAssembly.h src/mono/MonoClass.cpp src/mono/MonoClass.h src/mono/Mono.h src/mono/MonoDomain.cpp src/mono/MonoDomain.h src/mono/Mono.cpp)
set_target_properties(monochrome PROPERTIES PUBLIC_HEADER "include/monochrome.h")

target_link_libraries(monochrome mono-2.0-sgen)

add_custom_command(
    TARGET monochrome POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_BINARY_DIR}/bin/monochrome.dll
    ${DEADLINK_BINARY_DIR}/monochrome.dll
)

