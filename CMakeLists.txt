cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
set(PROJECT_NAME BattleCity)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME} src/main.cpp)


add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)
add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)
