cmake_minimum_required(VERSION 3.25)
project(Argentea C)
set(CMAKE_C_STANDARD 23)

add_library(Argentea SHARED src/dllmain.def src/dllmain.c src/lifecycle.c src/lifecycle.h src/shim_bridge/shim_bridge.c src/shim_bridge/shim_bridge.h src/shim_bridge/shims/x3daudio.h src/shim_bridge/shims/xinput.h src/shim_bridge/shims/dinput8.h src/shim_bridge/shims/dxgi.h src/shim_bridge/shims/dinput8.c src/shim_bridge/shims/shims.h src/shim_bridge/shims/dxgi.c src/shim_bridge/shims/x3daudio.c src/shim_bridge/shims/xinput.c)
target_link_libraries(Argentea shlwapi)

set_target_properties(Argentea PROPERTIES PREFIX "")
set_target_properties(Argentea PROPERTIES OUTPUT_NAME "dxgi")
set_source_files_properties(src/dllmain.def PROPERTIES HEADER_FILE_ONLY TRUE)