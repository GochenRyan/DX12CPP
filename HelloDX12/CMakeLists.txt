project(HelloDX12)

file(GLOB_RECURSE PRIVATE_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

file(GLOB_RECURSE PRIVATE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

set(CMAKE_WIN32_EXECUTABLE TRUE)

add_executable(HelloDX12 main.cpp d3dApp.cpp InitDirect3DApp.cpp)
target_sources(HelloDX12 PRIVATE ${PRIVATE_SOURCES} ${PRIVATE_HEADERS})
source_group("Private" FILES ${PRIVATE_HEADERS} ${PRIVATE_SOURCES})

target_link_libraries(HelloDX12 PRIVATE d3dcompiler d3d12 dxgi)
target_link_libraries(HelloDX12 PRIVATE Common)

add_custom_command(TARGET HelloDX12 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:Common>
    $<TARGET_FILE_DIR:HelloDX12>)