# Livox_WS
主要在 /Livox_WS/src/LIO-SAM-master/config/param.yaml 中设置参数;
  pointCloudTopic: 接收的点云话题
  imuTopic: 接收的imu话题

  lidarFrame: 
  baselinkFrame: 

  extrinsicRot: [1, 0, 0,
                  0, 1, 0,
                  0, 0, 1]
  extrinsicRPY: [1, 0, 0,
                  0, 1, 0,
                  0, 0, 1]
  extrinsicTrans: [0.05512, 0.02226, -0.0297]

具体参数设置可以参考 github上lio-sam的README.md

从livox格式点云转换为pointcloud2点云格式的文件为:/Livox_WS/src/livox_to_pointcloud2-master
/Livox_WS/src/livox_to_pointcloud2-master/src/livox_to_pointcloud2_ros1.cpp中,主要更改下边这句中的话题:
 points_sub = nh.subscribe("/livox/lidar_3JEDHB300100911", 10, &LivoxToPointCloud2::callback, this);
运行节点就可以转换为Pointcloud2类型的"/livox/points"的点云话题

注:
我已经在/Livox_WS/src/LIO-SAM-master/launch/module_loam.launch中添加了格式转换的节点;
所以只需要运行 roslaunch lio_sam run.launch即可,无需单独运行livox_to_pointcloud2-master功能包中的节点.
