#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Int8.h>
#include <std_msgs/Float32.h>
using namespace std;

void callback_range_front(const std_msgs::Float32& msg) {
    ROS_INFO("/range_front\t:\t%f\n\n", msg.data);
}
void callback_range_back(const std_msgs::Float32& msg) {
    ROS_INFO("/range_back\t:\t%f\n\n", msg.data);
}
void callback_range_right(const std_msgs::Float32& msg) {
    ROS_INFO("/range_right\t:\t%f\n\n", msg.data);
}
void callback_range_left(const std_msgs::Float32& msg) {
    ROS_INFO("/range_left\t:\t%f\n\n", msg.data);
}

void callback_img_center(const std_msgs::Int8& msg) {
    ROS_INFO("/img_center\t:\t%d\n\n", msg.data);
}
void callback_img_right(const std_msgs::Int8& msg) {
    ROS_INFO("/img_right\t:\t%d\n\n", msg.data);
}
void callback_img_left(const std_msgs::Int8& msg) {
    ROS_INFO("/img_left\t:\t%d\n\n", msg.data);
}

void callback_robot_state(const std_msgs::Int8& msg) {
    ROS_INFO("/robot_state\t:\t%d\n\n", msg.data);
}
void callback_robot_ang(const std_msgs::Int8& msg) {
    ROS_INFO("/robot_ang\t:\t%d\n\n", msg.data);
}

int main(int argc, char **argv){
  ros::init(argc, argv, "jakunen17_master");
  ros::NodeHandle nh;
  ros::Subscriber sub_range_front = nh.subscribe("/range_ahead", 100, callback_range_front);
  ros::Subscriber sub_range_back = nh.subscribe("/range_back", 100, callback_range_back);
  ros::Subscriber sub_range_right = nh.subscribe("/range_right", 100, callback_range_right);
  ros::Subscriber sub_range_left = nh.subscribe("/range_left", 100, callback_range_left);
  ros::Subscriber sub_img_center = nh.subscribe("/img_c", 100, callback_img_center);
  ros::Subscriber sub_img_right = nh.subscribe("/img_r", 100, callback_img_right);
  ros::Subscriber sub_img_left = nh.subscribe("/img_l", 100, callback_img_left);
  ros::Subscriber sub_robot_state = nh.subscribe("/robot_state", 100, callback_robot_state);
  ros::Subscriber sub_robot_ang = nh.subscribe("/robot_ang", 100, callback_robot_ang);
  ros::spin();
  return 0;
}