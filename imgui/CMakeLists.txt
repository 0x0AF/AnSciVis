file(GLOB_RECURSE IMGUI_SOURCE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
file(GLOB_RECURSE IMGUI_HEADER RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.hpp *.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

add_library(imgui STATIC
        ${IMGUI_SOURCE}
        ${IMGUI_HEADER})
