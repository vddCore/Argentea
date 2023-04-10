cmake_minimum_required(VERSION 3.25)
project(Argentea C)
set(CMAKE_C_STANDARD 23)

if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

add_library(Argentea SHARED src/dllmain.def src/dllmain.c src/lifecycle.c src/lifecycle.h src/shim_bridge.c src/shim_bridge.h src/shims/x3daudio.h src/shims/xinput.h src/shims/dinput8.h src/shims/dxgi.h src/shims/dinput8.c src/shims/shims.h src/shims/dxgi.c src/shims/x3daudio.c src/shims/xinput.c)
target_link_libraries(Argentea shlwapi)

set_target_properties(Argentea PROPERTIES PREFIX "")
set_target_properties(Argentea PROPERTIES OUTPUT_NAME "dxgi")
set_source_files_properties(src/dllmain.def PROPERTIES HEADER_FILE_ONLY TRUE)