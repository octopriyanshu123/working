# cmake_minimum_required(VERSION 3.10)
# project(ArithmeticOperations VERSION 1.0)

# # Create a static library
# add_library(ArithmeticLibStatic STATIC ArithmeticLib.cpp)

# # Create a shared (dynamic) library
# add_library(ArithmeticLibShared SHARED ArithmeticLib.cpp)

# # Create an executable that uses the library
# add_executable(main_program main.cpp)

# # Link the executable with both libraries (choose one)
# target_link_libraries(main_program ArithmeticLibStatic)
# # Or link to the shared library (you can choose one of these)
# # target_link_libraries(main_program ArithmeticLibShared)

# # Install both static and shared libraries
# install(TARGETS ArithmeticLibStatic ArithmeticLibShared DESTINATION lib)

# # Install header files into the include folder
# install(FILES ArithmeticLib.h DESTINATION include)

# # Install the executable into the bin folder
# install(TARGETS main_program DESTINATION bin)



cmake_minimum_required(VERSION 3.10)
project(NewProject)

# Specify the install directory for finding the libraries and headers
set(CMAKE_PREFIX_PATH "/path/to/install")

# Find the installed library
find_library(ArithmeticLibStatic NAMES ArithmeticLibStatic PATHS ${CMAKE_PREFIX_PATH}/lib)
find_library(ArithmeticLibShared NAMES ArithmeticLibShared PATHS ${CMAKE_PREFIX_PATH}/lib)

# Find the installed header file
find_path(ArithmeticLib_INCLUDE_DIR NAMES ArithmeticLib.h PATHS ${CMAKE_PREFIX_PATH}/include)

# Create the executable for the new project
add_executable(new_program main.cpp)

# Include the header from the installed directory
include_directories(${ArithmeticLib_INCLUDE_DIR})

# Link the executable to the static or shared library (choose one)
target_link_libraries(new_program ${ArithmeticLibStatic})
# Or use the shared library:
# target_link_libraries(new_program ${ArithmeticLibShared})
