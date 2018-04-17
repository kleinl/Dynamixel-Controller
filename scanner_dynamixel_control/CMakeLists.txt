cmake_minimum_required(VERSION 2.8.3)
project(scanner_dynamixel_control)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg message_generation)

## Declare a catkin package
catkin_package()

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(dxl_control src/dxl_control.cpp)
target_link_libraries(dxl_control ${catkin_LIBRARIES})
