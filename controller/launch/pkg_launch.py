from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='controller',
            executable='joystick_node',
        ),
        Node(
            package='controller',
            executable='motors_driver_node',
        ),
    ])