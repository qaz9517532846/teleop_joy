#include <rclcpp/rclcpp.hpp>

#include <std_msgs/msg/bool.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <sensor_msgs/msg/joy.hpp>

#include <chrono>
#include <string>
#include <functional>

using std::placeholders::_1;
using namespace std::chrono_literals;

class teleop_joy : public rclcpp::Node
{
  public:
    teleop_joy();
    ~teleop_joy();

  private:
    void joyCallback(const sensor_msgs::msg::Joy::SharedPtr joy);

    int linear_x_, linear_y_, angular_;
    double l_scale_, a_scale_;

    bool onmi_;
    bool joy_priority_;

    int joy_relay_;

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_vel_pub_;
    rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr joy_priority_pub_;
    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr joy_sub_;
};