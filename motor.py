from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():

    bridge = Node(
    package='ros_gz_bridge',
    executable='parameter_bridge',
    arguments=[
        '/X3/gazebo/command/motor_speed@actuator_msgs/msg/Actuators@gz.msgs.Actuators',
        '/cmd_vel@geometry_msgs/msg/Twist@gz.msgs.Twist',
        '/world/quadcopter/dynamic_pose/info@geometry_msgs/msg/PoseArray@gz.msgs.Pose_V'
    ],
    output='screen'

)

    motor_node = Node(
        package='motor_controller',
        executable='motor_node',
        output='screen'
    )

    return LaunchDescription([
        bridge,
        motor_node
    ])