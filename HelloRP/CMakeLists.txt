project(HelloRP)

file(GLOB_RECURSE PRIVATE_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/*h"
)

file(GLOB_RECURSE PRIVATE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*cpp"
)

set(CMAKE_WIN32_EXECUTABLE TRUE)

add_executable(HelloRP main.cpp BoxApp.cpp)
target_sources(HelloRP PRIVATE ${PRIVATE_SOURCES} ${PRIVATE_HEADERS})
source_group("Private" FILES ${PRIVATE_HEADERS} ${PRIVATE_SOURCES})

target_link_libraries(HelloRP PRIVATE d3dcompiler d3d12 dxgi)
target_link_libraries(HelloRP PRIVATE Common)

add_custom_command(TARGET HelloRP POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:Common>
    $<TARGET_FILE_DIR:HelloRP>)

set(SHADERS_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Shaders")
set(SHADERS_DEST_DIR "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY ${SHADERS_SRC_DIR} DESTINATION ${SHADERS_DEST_DIR})