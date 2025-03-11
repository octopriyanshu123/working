#include <iostream>

int main() {
    std::cout << "cmake_minimum_required(VERSION 3.5)\n"
              << "project(main)\n"
              << "add_executable(foo test.cpp)" << std::endl;

    std::cout << "cmake .. -G \"Unix Makefiles\"" << std::endl;
    std::cout << "cmake .. -G Ninja" << std::endl;
    return 0;
}
