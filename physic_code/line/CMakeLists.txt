cmake_minimum_required(VERSION 3.10)

project(SunAndCircle)

find_package(OpenGL REQUIRED)  # Find OpenGL package
find_package(GLUT REQUIRED)    # Find GLUT (if you are using GLUT for window/context management)

add_executable(SunAndCircle src/main.cpp)

# Link against OpenGL and GLU (GLU is required for gluPerspective)
target_link_libraries(SunAndCircle OpenGL::OpenGL GLUT::GLUT)



