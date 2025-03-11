# Use the official ROS 2 Humble base image
FROM ros:humble-ros-base

# Set environment variables for ROS 2
ENV LANG=C.UTF-8
ENV LC_ALL=C.UTF-8

# Install dependencies including Python and X11 libraries
RUN apt-get update && \
    apt-get install -y \
    python3-pip \
    python3-colcon-common-extensions \
    python3-rosdep \
    build-essential \
    x11-apps \
    libgl1-mesa-glx \
    libglib2.0-0 && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Create a workspace and copy your packages into the workspace
RUN mkdir -p /ros2_ws/src
WORKDIR /ros2_ws

# Copy package directories into the workspace
COPY ./my_actuator_ros2 /ros2_ws/src/my_actuator_ros2
COPY ./interfaces /ros2_ws/src/interfaces

# Initialize rosdep
RUN sudo apt update && sudo apt upgrade -y vim
RUN sudo apt-get install libboost-dev -y vim
RUN rosdep update

# Install dependencies for your packages
RUN rosdep install --from-paths src --ignore-src -r -y

# Make the Resource Folder for the Nessary Package CppLinuxSerial , Rmd
WORKDIR /ros2_ws
# Clone CppLinuxSerial And Build 
RUN mkdir Resource && cd Resource && git clone https://github.com/gbmhunter/CppLinuxSerial.git 
WORKDIR /ros2_ws/Resource/CppLinuxSerial
RUN mkdir build && cd build && cmake .. && make && sudo make install && sudo ldconfig

# Copy the libRmd_Library From ./ and Build
WORKDIR /ros2_ws/Resource
COPY ./libRmd_Library.so /usr/lib/

# Build the ROS 2 workspace One By One all package 
WORKDIR /ros2_ws
RUN . /opt/ros/humble/setup.sh && colcon build --packages-select interfaces && colcon build --packages-select my_actuator_ros2
WORKDIR /ros2_ws

RUN cd /ros2_ws/src/my_actuator_ros2/src
#RUN chmod +x my_actuator_control.cpp

# Source ROS 2 setup files and workspace setup
RUN echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc
RUN echo "source /ros2_ws/install/setup.bash" >> ~/.bashrc

# Create an entrypoint script to source ROS 2 setup files and run the launch file
COPY ros_entrypoint.sh /ros_entrypoint.sh
RUN chmod +x /ros_entrypoint.sh

# Set the entrypoint to the custom entrypoint script
ENTRYPOINT ["/ros_entrypoint.sh"]

# Default command to be executed in the container
CMD ["ros2", "launch", "my_actuator_ros2", "main.launch.py"]*
