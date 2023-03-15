#include <iostream>

#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <livox_ros_driver/CustomMsg.h>

#define ROS1
#include <livox_to_pointcloud2/livox_converter.hpp>

bool Convert_flag=1;
namespace livox_to_pointcloud2 {

class LivoxToPointCloud2 {
public:
  LivoxToPointCloud2() : nh("~") {
    points_pub = nh.advertise<sensor_msgs::PointCloud2>("/livox/points", 10);
    points_sub = nh.subscribe("/livox/lidar_3JEDHB300100911", 10, &LivoxToPointCloud2::callback, this);
  }

  void callback(const livox_ros_driver::CustomMsg::ConstPtr& livox_msg) {
    if(Convert_flag) {
       ROS_INFO("Converting Livox_point to Pointcloud2.");
       Convert_flag=0;
    }
    const auto points_msg = converter.convert(*livox_msg);
    points_pub.publish(points_msg);
  }

private:
  ros::NodeHandle nh;
  ros::Subscriber points_sub;
  ros::Publisher points_pub;

  LivoxConverter converter;
};

}

int main(int argc, char** argv) {
  ros::init(argc, argv, "livox_to_pointcloud2");
  livox_to_pointcloud2::LivoxToPointCloud2 node;
  
  ROS_INFO("Convert pointcloud function start");
  ROS_INFO("\033[1;32m----> Convert Pointcloud Function Started.\033[0m");

  ros::spin();

  return 0;
}