project(HelloDX12)

file(GLOB_RECURSE PRIVATE_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

file(GLOB_RECURSE PRIVATE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_executable(HelloDX12 d3dApp.cpp InitDirect3DApp.cpp)
target_sources(HelloDX12 PRIVATE ${PRIVATE_SOURCES} ${PRIVATE_HEADERS})
source_group("Private" FILES ${PRIVATE_HEADERS} ${PRIVATE_SOURCES})

target_link_libraries(HelloDX12 PRIVATE Common)