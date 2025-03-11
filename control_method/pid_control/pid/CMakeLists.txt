cmake_minimum_required(VERSION 3.10)
project(PID)

# Set the version of your library
set(PID_VERSION_MAJOR 1)
set(PID_VERSION_MINOR 0)

# Specify the include directory for headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# Create the shared library
add_library(pid SHARED src/PID.cpp)

# Set the installation directory for the library
set(LIBRARY_INSTALL_DIR /usr/lib)

# Install the library
install(TARGETS pid
        LIBRARY DESTINATION ${LIBRARY_INSTALL_DIR}
        COMPONENT PID)

# Install the header files
install(DIRECTORY include/ DESTINATION /usr/include)

# Create symlink for library
install(CODE "execute_process(COMMAND ln -s ${LIBRARY_INSTALL_DIR}/libpid.so /usr/lib/libpid.so)")

# Set the pkgconfig file
set(PKG_CONFIG_LIBDIR /usr/lib/pkgconfig)
