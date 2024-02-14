#include "p3dx_driver/joy_2_twist.hpp"
#include <string>



Joy2Twist::Joy2Twist() : nh_("~")
{
    joy_sub_ = nh_.subscribe("/joy", 0, &Joy2Twist::joy_callback_, this);
    cmd_vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/RosAria/cmd_vel", 10);
    nh_.getParam("/RosAria/linear/x/max_velocity", max_linear_vel_);
    nh_.getParam("/RosAria/angular/z/max_velocity", max_angular_vel_);
    timer_ = nh_.createTimer(ros::Duration(0.1), &Joy2Twist::timerCallback_, this);

    ROS_INFO("max_linear_vel:%.3f  max_angular_vel:%.3f",max_linear_vel_,max_angular_vel_);
}

void Joy2Twist::joy_callback_(const sensor_msgs::Joy::ConstPtr& msg)
{
    sensor_msgs::Joy tmp = *msg;

    cmd_vel_.linear.x = tmp.axes[1] * max_linear_vel_;
    cmd_vel_.linear.y = tmp.axes[0] * max_linear_vel_;
    cmd_vel_.angular.z = tmp.axes[3] * max_angular_vel_;
    
}
void Joy2Twist::timerCallback_(const ros::TimerEvent& e){
    cmd_vel_pub_.publish(cmd_vel_);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "joy2twist");
  Joy2Twist node;
  ros::spin();
  return 0;
}