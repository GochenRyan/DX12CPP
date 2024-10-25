file(GLOB_RECURSE PUBLIC_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/Public/*.h"
)
file(GLOB_RECURSE PRIVATE_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/Private/*.h"
)

file(GLOB_RECURSE PRIVATE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/Private/*.cpp"
)

add_library(Common SHARED ${PRIVATE_SOURCES})

target_sources(Common PRIVATE ${PRIVATE_SOURCES} ${PRIVATE_HEADERS})
target_sources(Common PUBLIC ${PUBLIC_HEADERS})

source_group("Public" FILES ${PUBLIC_HEADERS})
source_group("Private" FILES ${PRIVATE_HEADERS} ${PRIVATE_SOURCES})

target_include_directories(Common
    PUBLIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/Public
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/Private
)

get_target_property(dirs Common INCLUDE_DIRECTORIES)
message(STATUS "Common include directories: ${dirs}")