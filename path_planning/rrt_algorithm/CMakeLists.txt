cmake_minimum_required(VERSION 3.16.3)
project(rrt_visulizer)

add_executable(${PROJECT_NAME} main2.cpp)
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
