cmake_minimum_required(VERSION 3.5)
project(interfaces)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED) 
find_package(rclcpp REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)

# Include directories
include_directories(
  include
)


rosidl_generate_interfaces(${PROJECT_NAME}
   "msg/Plot.msg"
   "msg/Anglinarr.msg"
   "srv/RelayControl.srv"
   "msg/Healthinfo.msg"
   "msg/Motorspeed.msg"

   DEPENDENCIES geometry_msgs std_msgs

)



if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)

  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
