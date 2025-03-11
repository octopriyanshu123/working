# from launch import LaunchDescription
# from launch_ros.actions import Node
# from ament_index_python.packages import get_package_share_directory , get_package_prefix
# import os
# from launch.actions import ExecuteProcess

# def generate_launch_description():
#     pkgPath = get_package_share_directory('robotic_arms_control')
#     urdfFile = os.path.join(pkgPath, 'urdf', 'bazu.urdf')

#     mesh_pkg_share_dir = os.pathsep + os.path.join(get_package_prefix('robotic_arms_control'), 'share')

#     if 'GAZEBO_MODEL_PATH' in os.environ:
#         os.environ['GAZEBO_MODEL_PATH'] += mesh_pkg_share_dir
#     else:
#         os.environ['GAZEBO_MODEL_PATH'] =  mesh_pkg_share_dir

#     return LaunchDescription([
#         Node(
#             package='robot_state_publisher',
#             executable='robot_state_publisher',
#             name='robot_state_publisher',
#             output='screen',
#             arguments=[urdfFile]),

#         ExecuteProcess(
#             cmd=['gazebo', '--verbose', '-s', 'libgazebo_ros_factory.so'],
#             output='screen'),

#         Node(
#             package='gazebo_ros',
#             executable='spawn_entity.py',
#             name='robot_spawner',
#             output='screen',
#             arguments=["-topic", "/robot_description", "-entity", "bazu"]),

#     ])



from ament_index_python.packages import get_package_share_directory, get_package_prefix
from launch import LaunchDescription
from launch.actions import (DeclareLaunchArgument, SetEnvironmentVariable, IncludeLaunchDescription, SetLaunchConfiguration, ExecuteProcess)
from launch.substitutions import PathJoinSubstitution, LaunchConfiguration, TextSubstitution
from launch_ros.actions import Node
from launch.launch_description_sources import PythonLaunchDescriptionSource
import os

def generate_launch_description():
    # Get package directories
    pkg_ros_gz_sim = get_package_share_directory('ros_gz_sim')
    #pkg_spaceros_gz_sim = get_package_share_directory('spaceros_gz_sim')
    pkg_robotic_arms_control = get_package_share_directory('robotic_arms_control')

    # File paths
    gz_launch_path = PathJoinSubstitution([pkg_ros_gz_sim, 'launch', 'gz_sim.launch.py'])
    #gz_model_path = PathJoinSubstitution([pkg_spaceros_gz_sim, 'models'])
    urdf_file = os.path.join(pkg_robotic_arms_control, 'urdf', 'bazu.urdf')

    # Setup GAZEBO_MODEL_PATH
    mesh_pkg_share_dir = os.path.join(get_package_prefix('robotic_arms_control'), 'share')
    if 'GAZEBO_MODEL_PATH' in os.environ:
        os.environ['GAZEBO_MODEL_PATH'] += os.pathsep + mesh_pkg_share_dir
    else:
        os.environ['GAZEBO_MODEL_PATH'] = mesh_pkg_share_dir

    return LaunchDescription([
        # Gazebo world launch arguments
        DeclareLaunchArgument(
            'world',
            default_value='moon',
            choices=['moon', 'mars', 'enceladus'],
            description='World to load into Gazebo'
        ),
        SetLaunchConfiguration(name='world_file', 
                               value=[LaunchConfiguration('world'), 
                                      TextSubstitution(text='.sdf')]),
        #SetEnvironmentVariable('GZ_SIM_RESOURCE_PATH', gz_model_path),

        # Include Gazebo simulation launch
        # IncludeLaunchDescription(
        #     PythonLaunchDescriptionSource(gz_launch_path),
        #     launch_arguments={
        #         'gz_args': [PathJoinSubstitution([pkg_spaceros_gz_sim, 'worlds',
        #                                           LaunchConfiguration('world_file')])],
        #         'on_exit_shutdown': 'True'
        #     }.items(),
        # ),

        # Spawn robot in Gazebo
        Node(
            package='robot_state_publisher',
            executable='robot_state_publisher',
            name='robot_state_publisher',
            output='screen',
            arguments=[urdf_file]
        ),
        
        Node(
            package='gazebo_ros',
            executable='spawn_entity.py',
            name='robot_spawner',
            output='screen',
            arguments=["-topic", "/robot_description", "-entity", "bazu"]
        ),

        # Start Gazebo process
        ExecuteProcess(
            cmd=['gazebo', '--verbose', '-s', 'libgazebo_ros_factory.so'],
            output='screen'
        ),

        # Gazebo bridge node
        Node(
            package='ros_gz_bridge',
            executable='parameter_bridge',
            arguments=[],
            remappings=[],
            output='screen'
        ),
    ])
