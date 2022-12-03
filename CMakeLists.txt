cmake_minimum_required(VERSION 3.20)

project(ShooterController)

file(GLOB_RECURSE PROJECT_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.c")

find_package(OpenGL REQUIRED)
add_subdirectory(third_party/glfw)

add_library(
    glad STATIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/glad/include/glad/glad.h
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/glad/include/KHR/khrplatform.h
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/glad/src/glad.c
)

target_include_directories(
    glad
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/third_party/glad/include
)

add_executable(${CMAKE_PROJECT_NAME} ${PROJECT_SOURCES})

target_include_directories(
    ${CMAKE_PROJECT_NAME}

    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/third_party/
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/third_party/glfw/include
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/third_party/cglm/include
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/third_party/glad/include
)

target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    
    PUBLIC OpenGL::GL
    PUBLIC glfw
    PUBLIC glad
)