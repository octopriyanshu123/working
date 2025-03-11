# cmake version
cmake_minimum_required(VERSION 3.10)
project(rrtstar_visulizer)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)

# Find SFML package
find_package(SFML 2.5 REQUIRED graphics window system)

# Add the executable
add_executable(${PROJECT_NAME} src/main.cpp)

# Link SFML libraries
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

add_custom_target(
    ls_command
    COMMAND ls -l
    COMMENT "Listing files in the current directory"
)