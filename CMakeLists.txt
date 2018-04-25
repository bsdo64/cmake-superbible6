cmake_minimum_required(VERSION 3.11)
project(superbible6)

set(CMAKE_CXX_STANDARD 11)

file(COPY glsl DESTINATION ${CMAKE_BINARY_DIR})

find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED sdl2)
find_package(OpenGL REQUIRED)
find_package(GLM REQUIRED glm)

include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${glm_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})
link_libraries(${SDL_LIBRARIES})
link_libraries(${GLM_LIBRARIES})

add_executable(superbible6
        main.cpp
        BSApp.cpp
        BSApp.h
        glsl/vertex.glsl
        )

target_link_libraries(superbible6
        ${GLEW_LIBRARIES}
        ${SDL2_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${GLM_LIBRARIES}
        )

add_custom_target(copy_glsl_directory ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/glsl" "${CMAKE_BINARY_DIR}/glsl"
        COMMENT "Copy glsl directory to build tree"
        VERBATIM)
