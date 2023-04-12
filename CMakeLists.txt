cmake_minimum_required(VERSION 3.25)
project(Argentea C CXX)
set(CMAKE_C_STANDARD 23)

if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

set(DEADLINK_BINARY_DIR "E:\\Steam\\steamapps\\common\\Deadlink\\Deadlink\\Binaries\\Win64")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(argentea/monochrome/include)

add_subdirectory(argentea/dxgi_shim)
add_subdirectory(argentea/monochrome)