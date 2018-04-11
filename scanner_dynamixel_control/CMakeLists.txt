cmake_minimum_required(VERSION 2.8.3)
project(scanner_dynamixel_control)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg)

## Declare a catkin package
catkin_package()

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(talker src/talker.cpp)
target_link_libraries(talker ${catkin_LIBRARIES})
#add_dependencies(talker scanner_dynamixel_control_generate_messages_cpp)
