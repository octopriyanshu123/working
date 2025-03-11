from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    # Get the path to the package and the URDF file
    pkg_description = get_package_share_directory('panda_description')
    urdf_file = os.path.join(pkg_description, "urdf", 'arm_crawer.urdf')

    # Read the URDF file
    with open(urdf_file, 'r') as file:
        urdf_content = file.read()

    joint_state_publisher_node = Node(
        package="joint_state_publisher_gui",
        executable="joint_state_publisher_gui",
        name="JSP",
        output="screen",
    )

    joy_node = Node(
        package="joy",
        executable="joy_node",
        name="joy",
        output="screen",
    )


    robot_state_publisher_node = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        name="RSP",
        output="screen",
        parameters=[{'robot_description': urdf_content}]
    )
    rviz_node = Node(
        package="rviz2",
        executable="rviz2",
        name="rviz_gui",
        output="screen"
    )

    joy_control_node = Node(
        package="panda_description",
        executable="joy_control",
        name="joy_control",
        output="screen",
    )

    # Return the LaunchDescription
    return LaunchDescription([
        #joint_state_publisher_node,
        robot_state_publisher_node,
        #joy_node,
        rviz_node,
        # joy_control_node
    ])

if __name__ == '__main__':
    generate_launch_description()