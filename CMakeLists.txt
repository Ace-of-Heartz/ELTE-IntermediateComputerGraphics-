cmake_minimum_required(VERSION 3.29)
project(ParametricSurface)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/src/*.c
        ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Add header files
file(GLOB_RECURSE HEADER_FILES
        ${CMAKE_SOURCE_DIR}/src/*.h
        ${CMAKE_SOURCE_DIR}/src/*.hpp)

link_directories(${CMAKE_SOURCE_DIR}/lib)
message("${HEADER_FILES}")

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
message(STATUS "OpenGL included at ${OPENGL_INCLUDE_DIR}")

find_package(GLEW REQUIRED)
message(STATUS "GLEW included at ${GLEW_INCLUDE_DIR}")

find_package(SDL2 REQUIRED)
message(STATUS "SDL2 included at ${SDL2_INCLUDE_DIR}")

find_package(SDL2_image REQUIRED)

find_package(imgui REQUIRED)
#set(LIBS ${SDL2_LIBRARY} ${GLEW_LIBRARY})

# Define the include DIRs
include_directories(
        "${CMAKE_SOURCE_DIR}/src"
        "${CMAKE_SOURCE_DIR}/includes"
)

# Define the link libraries
#target_link_libraries(${PROJECT_NAME} ${LIBS})
target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL2::SDL2
        GLEW::glew
        imgui::imgui
        SDL2_image::SDL2_image
)




