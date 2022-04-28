import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch_ros.actions import Node
from launch.substitutions import LaunchConfiguration
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import ThisLaunchFileDir


def generate_launch_description():

    joy_config = os.path.join(get_package_share_directory('teleop_joy'), 'config', 'joy_params.yaml')

    return LaunchDescription([
        Node(
            package='joy',
            executable='joy_node',
            name='joy_node',
            output='screen',
            parameters=[joy_config]),

        Node(
            package='teleop_joy',
            executable='teleop_joy',
            name='teleop_joy',
            output='screen',
            parameters=[{"axis_linear_x": 1},
                        {"axis_linear_y": 0},
                        {"axis_angular": 3},
                        {"scale_angular": 1.0},
                        {"scale_linear": 1.0},
                        {"onmi_wheel": False},
                        {"axis_joy_priority": 4}]),
    ])