#include <teleop_joy/teleop_joy.h>

teleop_joy::teleop_joy() : private_nh_("~"),
                           joy_priority_(false)
{
    private_nh_.param<int>("axis_linear_x", linear_x_, 1);
    private_nh_.param<int>("axis_linear_y", linear_y_, 0);
    private_nh_.param<int>("axis_angular", angular_, 3);
    private_nh_.param<double>("scale_angular", a_scale_, 1);
    private_nh_.param<double>("scale_linear", l_scale_, 1);

    private_nh_.param<bool>("onmi_wheel", onmi_, false);

    private_nh_.param<int>("axis_joy_priority", joy_relay_, 4);
    
    vel_pub_ = nh_.advertise<geometry_msgs::Twist>("cmd_vel", 1);
    joy_priority_pub_ = nh_.advertise<std_msgs::Bool>("joy_priority", 1);
    joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &teleop_joy::joyCallback, this);
}

teleop_joy::~teleop_joy()
{

}

void teleop_joy::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
    geometry_msgs::Twist twist;
    std_msgs::Bool joy_priority;

    twist.linear.x = l_scale_ * joy->axes[linear_x_];
    twist.linear.y = onmi_ ? l_scale_ * joy->axes[linear_y_] : 0;
    twist.angular.z = a_scale_ * joy->axes[angular_];

    joy_priority.data = joy->buttons[joy_relay_] ? !joy_priority_ : joy_priority_;
    vel_pub_.publish(twist);
    joy_priority_pub_.publish(joy_priority);
}


int main(int argc, char** argv)
{
    ros::init(argc, argv, "teleop_joy");
    teleop_joy teleop_joy;
    
    ros::spin();
}