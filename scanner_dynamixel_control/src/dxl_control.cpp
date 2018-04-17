#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "std_msgs/String.h"
#include <stdlib.h>
#include <std_srvs/Empty.h>
#define _USE_MATH_DEFINES
#include <cmath>

ros::Publisher chatter_pub;
int degrees;
int counter = 0;
// Factor to calculate from degrees to radians.
double factor = (1.0/(180.0/M_PI));

bool move(std_srvs::Empty::Request &req, std_srvs::Empty::Response &res)
{
    std_msgs::Float64 message;
    // Calculate desired goal positon in radians.
    double position_degrees = counter*degrees;
    message.data = position_degrees*factor;

    ROS_INFO("%f degrees", position_degrees);

    // Send desired goal position.
    chatter_pub.publish(message);
    counter++;
    return true;
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "dxl_control");
    if (argc != 2) {
        ROS_WARN("WARNING: you should specify the degrees per step! Standard is set to 10.");
        degrees = 10;
    } else {
        ROS_INFO("INFO: you have set the degrees per step to: %s\n",argv[1]);
        degrees = atoi(argv[1]);
    } 
    ros::NodeHandle n;
    ros::ServiceServer service = n.advertiseService("dxl_control/move", move);
    // Send messages to "tilt_controller/command" to set target position.
    chatter_pub = n.advertise<std_msgs::Float64>("tilt_controller/command", 1000);
    // Wait for "chatter" to receive a message, then execute chatterCallback
    // routine
    // ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);
    ros::spin();
    return 0;
}
