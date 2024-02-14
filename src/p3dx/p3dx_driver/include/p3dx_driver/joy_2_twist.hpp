#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>

class Joy2Twist
{
public:
  ros::NodeHandle nh_;
  Joy2Twist();
  void joy_callback_(const sensor_msgs::Joy::ConstPtr& msg);
  void timerCallback_(const ros::TimerEvent& e);
  
private:
  ros::Subscriber joy_sub_;
  ros::Publisher cmd_vel_pub_;
  geometry_msgs::Twist cmd_vel_;
  ros::Timer timer_;
  float max_linear_vel_, max_angular_vel_;
};