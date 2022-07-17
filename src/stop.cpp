#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Int8.h>
#include <std_msgs/Float32.h>
using namespace std;
#include <stdio.h>

int robot_mode=0;
int stage = 0;
int cou=0;

int f_kyori = 0;
int b_kyori = 0;
int r_kyori = 0;
int l_kyori = 0;

void callback_range_front(const std_msgs::Float32& msg) {
    //ROS_INFO("/range_front\t:\t%f\n\n", msg.data);
    f_kyori =  msg.data;
}

void callback_robot_state(const std_msgs::Int8& msg) {
    if(msg.data<1)robot_mode=0;
    else if(msg.data<4)robot_mode=1;
    else robot_mode=2;
}

int main(int argc, char **argv){
  ros::init(argc, argv, "jakunen17_master");
  ros::NodeHandle nh;
  ros::Publisher pub_twist= nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
  ros::Publisher pub_hand_task = nh.advertise<std_msgs::Int8>("/hand_tast", 10);
  ros::Rate rate(10);
  geometry_msgs::Twist vel;
  std_msgs::Int8 fin;
  ros::Subscriber sub_robot_state = nh.subscribe("/robot_state", 100, callback_robot_state);
  ros::Subscriber sub_range_front = nh.subscribe("/range_ahead", 100, callback_range_front);
  while (ros::ok()) {

        vel.linear.x = 0.0;
        vel.linear.y = 0.0;
        vel.linear.z = 0.0;
        vel.angular.x = 0.0;
        vel.angular.y = 0.0;
        vel.angular.z = 0.0;
        pub_twist.publish(vel);
        fin.data=0;
        pub_hand_task.publish(fin);
        //if(robot_mode==1)stage++;

    //if(robot_mode==0)stage=0;
    if(robot_mode==2)stage=99;
    ros::spinOnce();
    rate.sleep();
  }
  return 0;
}