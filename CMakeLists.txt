cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(DX12CPP)

add_definitions(-D_UNICODE)
add_definitions(-DUNICODE)

add_subdirectory(Common)
add_subdirectory(HelloDX12)
add_subdirectory(HelloRP)
add_subdirectory(DrawGeometry)
add_subdirectory(LandAndWaves)