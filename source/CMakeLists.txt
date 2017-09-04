file(GLOB_RECURSE FRAMEWORK_SHADER_VERTEX RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.vert)
file(GLOB_RECURSE FRAMEWORK_SHADER_FRAGME RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.frag)
add_executable(MyVolumeRaycaster my_volume_raycaster.cpp
        ${FRAMEWORK_SHADER_VERTEX}
        ${FRAMEWORK_SHADER_FRAGME})
target_link_libraries(MyVolumeRaycaster framework ${CMAKE_DL_LIBS} ${GLEW_LIBRARIES} imgui ${OPENGL_LIBRARIES} ${SDL2_LIBRARIES} ${GLM_LIBRARIES} STB)
add_dependencies(MyVolumeRaycaster framework imgui STB)
install(TARGETS MyVolumeRaycaster DESTINATION .)

add_executable(TestEnv test_env.cpp
        ${FRAMEWORK_SHADER_VERTEX}
        ${FRAMEWORK_SHADER_FRAGME})
target_link_libraries(TestEnv framework ${CMAKE_DL_LIBS} ${GLEW_LIBRARIES} imgui ${OPENGL_LIBRARIES} ${SDL2_LIBRARIES} ${GLM_LIBRARIES} STB)
add_dependencies(TestEnv framework imgui STB)
install(TARGETS TestEnv DESTINATION .)