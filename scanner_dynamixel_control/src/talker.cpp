#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "std_msgs/String.h"
#include "dynamixel_controllers/SetCompliancePunch.h"
#include "dynamixel_controllers/SetComplianceSlope.h"
#include <stdlib.h>

ros::Publisher chatter_pub;
int degrees;
int counter = 0;
double factor = (1.0/(360.0/6.3));

void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
    std_msgs::Float64 message;
    double position_degrees = counter*degrees;
    message.data = position_degrees*factor;

    ROS_INFO("%f degrees", position_degrees);

    chatter_pub.publish(message);
    counter++;

    ros::spinOnce();
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");
  if (argc != 2) {
    ROS_WARN("WARNING: you should specify the degrees per step! Standard is set to 10.");
    degrees = 10;
  } else {
    ROS_INFO("INFO: you have set the degrees per step to: %s\n",argv[1]);
    degrees = atoi(argv[1]);
  } 

  ros::NodeHandle n;

  ros::ServiceClient client = n.serviceClient<dynamixel_controllers::SetCompliancePunch>("/dynamixel_controllers/set_compliance_punch");
  dynamixel_controllers::SetCompliancePunch srv;
  srv.request.punch = 15;
  client.call(srv);

  ros::ServiceClient client2 = n.serviceClient<dynamixel_controllers::SetComplianceSlope>("/dynamixel_controllers/set_compliance_slope");
  dynamixel_controllers::SetComplianceSlope srv2;
  srv2.request.slope = 64;
  client2.call(srv2);

  chatter_pub = n.advertise<std_msgs::Float64>("tilt_controller/command", 1000);
  ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);

  ros::spin();

  return 0;
}
