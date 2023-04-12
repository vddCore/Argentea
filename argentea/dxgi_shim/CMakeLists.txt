cmake_minimum_required(VERSION 3.25)
project(dxgi_shim C)
set(CMAKE_C_STANDARD 23)

add_library(dxgi_shim SHARED src/dllmain.def src/dllmain.c src/shim_lifecycle.c src/shim_lifecycle.h src/shim_bridge.c src/shim_bridge.h src/shims/x3daudio.h src/shims/xinput.h src/shims/dinput8.h src/shims/dxgi.h src/shims/dinput8.c src/shims/shims.h src/shims/dxgi.c src/shims/x3daudio.c src/shims/xinput.c src/shim_context.c src/shim_context.h src/monochrome_loader.c src/monochrome_loader.h)
target_link_libraries(dxgi_shim shlwapi)

set_source_files_properties(src/dllmain.def PROPERTIES HEADER_FILE_ONLY TRUE)

set_target_properties(dxgi_shim PROPERTIES PREFIX "")
set_target_properties(dxgi_shim PROPERTIES OUTPUT_NAME "dxgi")


add_custom_command(
    TARGET dxgi_shim POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_BINARY_DIR}/bin/dxgi.dll
    ${DEADLINK_BINARY_DIR}/dxgi.dll
)