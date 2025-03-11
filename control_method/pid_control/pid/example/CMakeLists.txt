# CMakeLists.txt for the new project (e.g., new_project)

cmake_minimum_required(VERSION 3.10)
project(example)

# Enable C++17 or later
set(CMAKE_CXX_STANDARD 17)

# Find the PID library installed on the system
find_package(PID REQUIRED)  # This will search for the PID library (pid.so)

# Specify the new project's source file
add_executable(example main.cpp)

# Link the PID library to the new project
target_link_libraries(speed_control PRIVATE pid)

# If PID is installed in a non-standard directory, you may need to specify the path:
# link_directories(/path/to/libpid)
# find_package(PID REQUIRED)
