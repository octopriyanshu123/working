#!/bin/bash

# Step 1: Clone the repository
echo "Cloning the repository..."
git clone <git-link> pid
cd pid || exit 1  # Exit if cd fails

# Step 2: Create the build directory
echo "Creating build directory..."
mkdir build
cd build || exit 1  # Exit if cd fails

# Step 3: Run CMake to configure the build
echo "Running CMake to configure the build..."
cmake .. || { echo "CMake configuration failed"; exit 1; }

# Step 4: Build the library
echo "Building the library..."
make || { echo "Build failed"; exit 1; }

# Step 5: Install the library
echo "Installing the library..."
sudo make install || { echo "Installation failed"; exit 1; }

# Step 6: Update the linker cache
echo "Updating the linker cache..."
sudo ldconfig || { echo "ldconfig failed"; exit 1; }

# Step 7: Create a symbolic link (optional but recommended)
echo "Creating a symbolic link for the library..."
sudo ln -s /usr/lib/libpid.so /usr/lib64/libpid.so || { echo "Failed to create symbolic link"; exit 1; }

# Script finished
echo "PID library installed successfully!"
