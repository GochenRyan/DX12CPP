aux_source_directory(. DIR_SRCS)
add_executable(HelloDX12 ${DIR_SRCS})

file(GLOB_RECURSE PRIVATE_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

file(GLOB_RECURSE PRIVATE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)
target_sources(HelloDX12 PRIVATE ${PRIVATE_SOURCES} ${PRIVATE_HEADERS})

target_link_libraries(HelloDX12 PRIVATE Common)