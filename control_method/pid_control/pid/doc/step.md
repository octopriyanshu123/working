To create a library that you can build and install using the steps you mentioned, we'll need to structure your project in a way that follows common CMake practices. This will allow you to use `cmake`, `make`, and `make install` to compile and install the library. Additionally, we'll provide the necessary CMake configuration to build a shared library (`libpid.so`) and enable the use of `ldconfig` and symbolic links.

### Project Structure
Here's an outline of the file structure we will create for your project:

```
pid/
├── CMakeLists.txt
├── src/
│   └── PID.cpp
├── include/
│   └── PID.h
└── build/  (This directory will be created during the build process)
```


### Step 4: Build and Install the Library

1. **Clone the repository**:

   Clone the repository to your local machine (replace `<git-link>` with your actual repository URL):

   ```sh
   git clone <git-link>
   cd pid
   ```

2. **Create the build directory**:

   ```sh
   mkdir build
   cd build
   ```

3. **Run CMake to configure the build**:

   ```sh
   cmake ..
   ```

   This will generate the necessary build files.

4. **Build the library**:

   ```sh
   make
   ```

   This will compile the library.

5. **Install the library**:

   ```sh
   sudo make install
   ```

   This installs the library and the header files to the appropriate system directories (`/usr/lib` for libraries, `/usr/include` for headers).

6. **Update the linker cache**:

   If necessary, run the following command to update the linker cache:

   ```sh
   sudo ldconfig
   ```

7. **Create a symbolic link** (optional but recommended):

   If the library is not found automatically by the linker, you can create a symbolic link for it in the `/usr/lib` directory:

   ```sh
   sudo ln -s /usr/lib/libpid.so /usr/lib64/libpid.so
   ```

   This step ensures that your library can be found by the linker when it's used in other projects or applications.

### Step 5: Using the Library in Other Projects

After installing the `pid` library, you can link it in other C++ projects by following these steps:

1. **Include the Header File**:
   In your project, include the header file `PID.h`:

   ```cpp
   #include <PID.h>
   ```

2. **Link the Library**:
   When compiling your C++ code, you can link the `pid` library by using the `-lpid` option with your compiler (e.g., `g++`):

   ```sh
   g++ -o my_program my_program.cpp -lpid
   ```

   This tells the compiler to link the program with the `libpid.so` library.

### Step 6: Cleanup and Testing

After completing the installation process, you should be able to use the `pid` library in your applications. Make sure to test that the library works correctly by writing a simple test program and compiling it with the `-lpid` flag to verify everything is set up properly.

### Summary

1. **CMake Configuration**: The `CMakeLists.txt` file sets up the build process for a shared library (`libpid.so`).
2. **Library Installation**: The `make install` command installs the shared library and headers.
3. **Symbolic Link**: A symbolic link is created for the library so it can be found by other programs.

Let me know if you need further clarification or additional assistance!


export LD_LIBRARY_PATH=/usr/lib:$LD_LIBRARY_PATH
