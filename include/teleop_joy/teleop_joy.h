#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>
#include <std_msgs/Bool.h>

class teleop_joy
{
    public:
      teleop_joy();
      ~teleop_joy();
    
    private:
      void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);

      ros::NodeHandle private_nh_;
      ros::NodeHandle nh_;
      
      int linear_x_, linear_y_, angular_;
      double l_scale_, a_scale_;

      bool onmi_, joy_priority_;

      int joy_relay_;

      ros::Publisher vel_pub_;
      ros::Publisher joy_priority_pub_;
      ros::Subscriber joy_sub_;
};