#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Int8.h>
#include <std_msgs/Float32.h>
using namespace std;
#include <stdio.h>

int robot_mode=0;
int stage = 0;
int cou=0;
std_msgs::Int8 ang_dir;

float f_kyori = -1;
float b_kyori = -1;
float r_kyori = -1;
float l_kyori = -1;
float sokudo = 0.1;
float gensoku= 0.07;

void callback_range_front(const std_msgs::Float32& msg) {
    //ROS_INFO("/range_front\t:\t%f\n\n", msg.data);
    f_kyori =  msg.data;
}
void callback_range_back(const std_msgs::Float32& msg) {
    //ROS_INFO("/range_back\t:\t%f\n\n", msg.data);
     b_kyori =  msg.data;
}
void callback_range_right(const std_msgs::Float32& msg) {
    //ROS_INFO("/range_right\t:\t%f\n\n", msg.data);
     r_kyori =  msg.data;
}
void callback_range_left(const std_msgs::Float32& msg) {
    //ROS_INFO("/range_left\t:\t%f\n\n", msg.data);
    l_kyori =  msg.data;
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
  ros::Publisher pub_tgt_ang = nh.advertise<std_msgs::Int8>("/tgt_ang", 10);
  ros::Rate rate(10);
  geometry_msgs::Twist vel;
  std_msgs::Int8 fin;
  ros::Subscriber sub_robot_state = nh.subscribe("/robot_state", 100, callback_robot_state);
  ros::Subscriber sub_range_front = nh.subscribe("/range_ahead", 100, callback_range_front);
  ros::Subscriber sub_range_back = nh.subscribe("/range_back", 100, callback_range_back);
  ros::Subscriber sub_range_right = nh.subscribe("/range_right", 100, callback_range_right);
  ros::Subscriber sub_range_left = nh.subscribe("/range_left", 100, callback_range_left);
  while (ros::ok()) {
    switch(stage){
      case 0:
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
        // stage++;
        stage++;
        
      case 1: //????????????
        cou++;
        vel.linear.x = sokudo;
        vel.linear.y = 0.0;
        vel.linear.z = 0.0;
        vel.angular.x = 0.0;
        vel.angular.y = 0.0;
        vel.angular.z = 0.0;
        // if(cou>=40){
        if(f_kyori<0.55){
          printf("aaaaa=\n");
          vel.linear.x = gensoku;
        }
        if(f_kyori<0.42 && r_kyori>0.0){
          cou=0;
          stage++;//????????????
        }
        pub_twist.publish(vel);
        break; 
    case 2: //???
        cou++;
        vel.linear.x = 0.0;
        vel.linear.y = -1*sokudo;
        vel.linear.z = 0.0;
        vel.angular.x = 0.0;
        vel.angular.y = 0.0;
        vel.angular.z = 0.0;
        //pub_twist.publish(vel);
        // if(cou>=40){
       if(r_kyori<0.65){
          printf("aaaaa=\n");
          vel.linear.y = -1*gensoku;
        }
       if(r_kyori<0.40 && r_kyori>0){
          cou=0;
          stage++;//????????????
        }
        //pub_twist.publish(vel);
        break;
    case 3: //????????????
        cou++;
        vel.linear.x = sokudo;
        vel.linear.y = 0.0;
        vel.linear.z = 0.0;
        vel.angular.x = 0.0;
        vel.angular.y = 0.0;
        vel.angular.z = 0.0;
        //pub_twist.publish(vel);
        // if(cou>=40){
        if(f_kyori<0.7){
          printf("aaaaa=\n");
          vel.linear.x = gensoku;
        }
        if(f_kyori<0.62 && f_kyori>0){
          cou=0;
          stage++;//????????????
        }
        pub_twist.publish(vel);
        break;
    case 4://?????????
        cou++;
        vel.linear.x = 0.0;
        vel.linear.y = 0.0;
        vel.linear.z = 0.0;
        vel.angular.x = 0.0;
        vel.angular.y = 0.0;
        vel.angular.z = 0.0;
        ang_dir.data=2;
        pub_tgt_ang.publish(ang_dir);
        if(cou>=40){
          cou=0;
          stage++;
        }
        break;
    case 5: //????????????
        vel.linear.x = 0.0;
        vel.linear.y = 0.0;
        if(r_kyori>0.33){
          printf("aaaaa=\n");
          vel.linear.y = -0.5*gensoku;
        }
        if(r_kyori<=0.34 && r_kyori>=0){
          cou=0;
          stage++;//????????????
        }
        pub_twist.publish(vel);
        break;
    case 6://?????????.???
        cou++;
        vel.linear.x = sokudo;
        vel.linear.y = 0.0;
        vel.linear.z = 0.0;
        vel.angular.x = 0.0;
        vel.angular.y = 0.0;
        vel.angular.z = 0.0;
        //pub_twist.publish(vel);
        // if(cou>=40){
       if(f_kyori<0.5 &&r_kyori<0.45){
          printf("aaaaa=\n");
          vel.linear.x = gensoku;
        }
        if(r_kyori<0.32){
          printf("aaaaa=\n");
          vel.linear.y = 0.05*gensoku;
        }
       if(f_kyori<0.44 && f_kyori>0){
          cou=0;
          stage++;//????????????
        }
        pub_twist.publish(vel);
        break;
      case 7://??????????????????
        cou++;
        vel.linear.x = 0.0;
        vel.linear.y = 0.0;
        vel.linear.z = 0.0;
        vel.angular.x = 0.0;
        vel.angular.y = 0.0;
        vel.angular.z = 0.0;
        ang_dir.data=0;
        pub_tgt_ang.publish(ang_dir);
        if(cou>=40){
          cou=0;
          stage++;
        }
        break;
      case 8://???????????????
        cou++;
        vel.linear.x = 0.0;
        vel.linear.y = -1*sokudo;
        vel.linear.z = 0.0;
        vel.angular.x = 0.0;
        vel.angular.y = 0.0;
        vel.angular.z = 0.0;
        //pub_twist.publish(vel);
        // if(cou>=40){
       if(l_kyori>0.5){
          printf("aaaaa=\n");
          vel.linear.y = -1*gensoku;
        }
       if(l_kyori>0.82){
          cou=0;
          stage++;//????????????
        }
        break;
      case 9: //?????????????????????
        cou++;
        vel.linear.x = -1*sokudo;
        vel.linear.y = 0.0;
        vel.linear.z = 0.0;
        vel.angular.x = 0.0;
        vel.angular.y = 0.0;
        vel.angular.z = 0.0;
        //pub_twist.publish(vel);
        // if(cou>=40){
        if(b_kyori<0.6){
          printf("aaaaa=\n");
          vel.linear.x = -1*gensoku;
        }
        if(r_kyori<0.45){
          printf("aaaaa=\n");
          vel.linear.y = 0.5*gensoku;
        }
        if(b_kyori<0.38 && b_kyori>0){
          cou=0;
          stage++;//????????????
        }
        pub_twist.publish(vel);
        break;
      case 10://?????????
        cou++;
        vel.linear.x = 0.0;
        vel.linear.y = 0.0;
        vel.linear.z = 0.0;
        vel.angular.x = 0.0;
        vel.angular.y = 0.0;
        vel.angular.z = 0.0;
        ang_dir.data=3;
        pub_tgt_ang.publish(ang_dir);
        if(cou>=40){
          cou=0;
          stage++;
        }
        break;
      case 11: //???????????????
        cou++;
        vel.linear.x = sokudo;
        vel.linear.y = 0.0;
        vel.linear.z = 0.0;
        vel.angular.x = 0.0;
        vel.angular.y = 0.0;
        vel.angular.z = 0.0;
        //pub_twist.publish(vel);
        // if(cou>=40){
        if(r_kyori>0.34){
          printf("aaaaa=\n");
          vel.linear.y = -0.1*gensoku;
        }
        if(l_kyori<0.6 && f_kyori<0.40){
          cou=0;
          stage++;//????????????
        }
        break;
      case 12://??????????????????
        cou++;
        vel.linear.x = -1*sokudo;
        vel.linear.y = 0.0;
        vel.linear.z = 0.0;
        vel.angular.x = 0.0;
        vel.angular.y = 0.0;
        vel.angular.z = 0.0;
        //pub_twist.publish(vel);
        // if(cou>=40){
        if(r_kyori>0.40){
          printf("aaaaa=\n");
          vel.linear.y = -0.1*gensoku;
         }
         if(r_kyori<0.30){
          printf("aaaaa=\n");
          vel.linear.y = 0.1*gensoku;
         }
        if(l_kyori<0.18){
          printf("aaaaa=\n");
          vel.linear.y = 0.5*gensoku;
         }
        if(b_kyori>0.38){
          vel.linear.x = -1*sokudo;
        }
       if(b_kyori<0.38 && b_kyori>0){
          cou=0;
          stage++;//????????????
        }
        break;
      case 13://?????????
        cou++;
        vel.linear.x = 0.0;
        vel.linear.y = 0.0;
        vel.linear.z = 0.0;
        vel.angular.x = 0.0;
        vel.angular.y = 0.0;
        vel.angular.z = 0.0;
        ang_dir.data=0;
        pub_tgt_ang.publish(ang_dir);
        if(cou>=40){
          cou=0;
          stage=99;
        }
        break;
      case 99:
        vel.linear.x = 0.0;
        vel.linear.y = 0.0;
        vel.linear.z = 0.0;
        vel.angular.x = 0.0;
        vel.angular.y = 0.0;
        vel.angular.z = 0.0;
        pub_twist.publish(vel);
        //if(robot_mode==0)stage=0;
        break;
    }
    pub_twist.publish(vel);
    //if(robot_mode==0)stage=0;
    //if(robot_mode==2)stage=99;
    printf("state=%d\n",stage);
    printf("F_kyori:%f\n",f_kyori);
    printf("B_kyori:%f\n",b_kyori);
    printf("R_kyori:%f\n",r_kyori);
    printf("L_kyori:%f\n\n",l_kyori);
    ros::spinOnce();
    rate.sleep();
  }
  return 0;
}