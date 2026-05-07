import rclpy
from rclpy.node import Node
from actuator_msgs.msg import Actuators
from geometry_msgs.msg import PoseArray


class PID:
    def __init__(self, kp, ki, kd):
        self.kp = kp
        self.ki = ki
        self.kd = kd

        self.prev_error = 0.0
        self.integral = 0.0

    def step(self, error, dt):
        self.integral += error * dt
        derivative = (error - self.prev_error) / dt
        self.prev_error = error

        return self.kp * error + self.ki * self.integral + self.kd * derivative


class MotorNode(Node):

    def __init__(self):
        super().__init__('alt_hold')

        self.pub = self.create_publisher(
            Actuators,
            '/X3/gazebo/command/motor_speed',
            10
        )

        self.create_subscription(
            PoseArray,
            '/world/quadcopter/dynamic_pose/info',
            self.pose_cb,
            10
        )

        self.timer = self.create_timer(0.05, self.control_loop)

        # TARGET
        self.target_z = 2.0
        self.current_z = 0.0

        # PID (do strojenia!)
        self.pid = PID(kp=40.0, ki=0.0, kd=10.0)

        # baza ciągu (utrzymanie zawisu bez korekty)
        self.base_thrust = 700.0

        self.last_time = self.get_clock().now()

    def pose_cb(self, msg: PoseArray):

        self.current_z = msg.poses[0].position.z
        return

    def control_loop(self):
        now = self.get_clock().now()
        dt = (now - self.last_time).nanoseconds * 1e-9
        self.last_time = now

        error = self.target_z - self.current_z

        correction = self.pid.step(error, dt)

        thrust = self.base_thrust + correction

        # ograniczenia bezpieczeństwa
        thrust = max(0.0, min(thrust, 1000.0))

        msg = Actuators()
        msg.velocity = [thrust, thrust, thrust, thrust]

        self.pub.publish(msg)

        self.get_logger().info(
            f"z={self.current_z:.2f} target={self.target_z:.2f} thrust={thrust:.2f}"
        )


def main():
    rclpy.init()
    node = MotorNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()