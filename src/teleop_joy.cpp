#include <teleop_joy/teleop_joy.h>

teleop_joy::teleop_joy() : Node("teleop_joy"),
                           joy_priority_(false)
{
    this->declare_parameter<int>("axis_linear_x", 1);
    this->declare_parameter<int>("axis_linear_y", 0);
    this->declare_parameter<int>("axis_angular", 3);

    this->declare_parameter<double>("scale_angular", 1);
    this->declare_parameter<double>("scale_linear", 1);

    this->declare_parameter<bool>("onmi_wheel", false);
    this->declare_parameter<int>("axis_joy_priority", 4);

    this->get_parameter("axis_linear_x", linear_x_);
    this->get_parameter("axis_linear_y", linear_y_);
    this->get_parameter("axis_angular", angular_);
    this->get_parameter("scale_angular", a_scale_);
    this->get_parameter("scale_linear", l_scale_);
    this->get_parameter("onmi_wheel", onmi_);
    this->get_parameter("axis_joy_priority", joy_relay_);

    joy_sub_ = this->create_subscription<sensor_msgs::msg::Joy>("joy", 10, std::bind(&teleop_joy::joyCallback, this, _1));
    cmd_vel_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);
    joy_priority_pub_ = this->create_publisher<std_msgs::msg::Bool>("joy_priority", 10);
}

teleop_joy::~teleop_joy()
{
    
}

void teleop_joy::joyCallback(const sensor_msgs::msg::Joy::SharedPtr joy)
{
    auto twist = geometry_msgs::msg::Twist();
    auto joy_priority = std_msgs::msg::Bool();

    twist.linear.x = l_scale_ * joy->axes[linear_x_];
    twist.linear.y = onmi_ ? l_scale_ * joy->axes[linear_y_] : 0;
    twist.angular.z = a_scale_ * joy->axes[angular_];

    if(joy->buttons[joy_relay_])
    {
        joy_priority_ = !joy_priority_;
        joy_priority.data = joy_priority_;
        joy_priority_pub_->publish(joy_priority);

        twist.linear.x = 0;
        twist.linear.y = 0;
        twist.angular.z = 0;
    }

    cmd_vel_pub_->publish(twist);
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<teleop_joy>());
  rclcpp::shutdown();
  return 0;
}