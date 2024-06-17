cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
set(PROJECT_NAME BattleCity)
project(${PROJECT_NAME})


add_executable(${PROJECT_NAME} 
src/Renderer/ShaderProgram.cpp
src/Renderer/ShaderProgram.h
src/Resources/ResourceManager.h
src/Resources/ResourceManager.cpp
src/Resources/stb_image.h
src/main.cpp)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)
add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)
