cmake_minimum_required(VERSION 3.10)

# Set the project name
project(RayTracing)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)

# Find SDL2 package
find_package(SDL2 REQUIRED)

# Add the executable
add_executable(raytracing src/main.cpp)

# Link the executable to SDL2
target_link_libraries(raytracing SDL2::SDL2)
