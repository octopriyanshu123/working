# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(random_cuboid)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenGL package (GLVND is preferred)
find_package(OpenGL REQUIRED)

# Find GLUT (you may need to install GLUT or FreeGLUT)
find_package(GLUT REQUIRED)

# Manually find the GLU package (GLU is part of libglu1-mesa)
find_library(GLU_LIBRARY NAMES GLU GLU32 libGLU)

# Add the executable
add_executable(${PROJECT_NAME} src/main.cpp)

# Link the libraries
target_link_libraries(${PROJECT_NAME} OpenGL::GL GLUT::GLUT ${GLU_LIBRARY})
