cmake_minimum_required(VERSION 3.8)
project(AnSciVis)

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/framework)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/source)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(glm REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

include_directories(stb-image)
include_directories(imgui)

add_subdirectory(stb-image)
add_subdirectory(imgui)
add_subdirectory(framework)
add_subdirectory(source)
