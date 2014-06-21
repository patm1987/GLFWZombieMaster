project(GLFWZombieMaster)
cmake_minimum_required(VERSION 2.8)

# src directory
aux_source_directory(src SRC_LIST)
aux_source_directory(src/utils SRC_LIST)
aux_source_directory(src/scenegraph SRC_LIST)
aux_source_directory(src/entity SRC_LIST)
include_directories(src)
add_executable(${PROJECT_NAME} ${SRC_LIST})

# glm
add_subdirectory(libs/glm)
include_directories(libs/glm)

# link in glfw
add_subdirectory(libs/glfw-3.0.4)
include_directories(libs/glfw-3.0.4/include)
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})
