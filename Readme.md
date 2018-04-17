## 1. Software Installation

### 1.1 Install ROS
Tested with ROS Kinetic Kame:
http://wiki.ros.org/kinetic/Installation/Ubuntu
```
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
sudo apt-key adv --keyserver hkp://ha.pool.sks-keyservers.net:80 --recv-key 421C365BD9FF1F717815A3895523BAEEB01FA116
sudo apt-get update
sudo apt-get install ros-kinetic-ros-base
```
### 1.2 Setup ROS environment
Add "source /opt/ros/kinetic/setup.bash" to your ~/.bashrc
```
source ~/.bashrc
```
Create the catkin workspace with:
```
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws
catkin_make
```
Add "source ~/catkin_ws/devel/setup.bash" to your ~/.bashrc
```
source ~/.bashrc
```

### 1.3 Install dynamixel_controller package for ros
```
sudo apt-get install ros-kinetic-dynamixel-controllers
```

### 1.4 Copy the code
Copy the "scanner_dynamixel_control folder to ~/catkin_ws/src
```
cd ~/catkin_ws
catkin_make
```
## 2. Hardware Setup
### 2.1 Power the motor
Connect the motor to a voltage source (red is plus, black minus) with 9-12V.
### 2.2 Connect controller with computer
Plug in the usb2dynamixel stick to your computer with the communication slider set to TTL.
### 2.3 Connect controller with motor
Connect the motor with the TTL port of the usb2dynamixel.

## 3. Run the table.
### 3.1 Make your USB port writeable
could be different depending on the port
```
sudo chmod a+rw /dev/ttyUSB0
```
### 3.2 Launch the controller manager
```
roslaunch scanner_dynamixel_control controller_manager.launch
```
### 3.3 Start the tilt_controller 
open a new terminal.
```
roslaunch scanner_dynamixel_control start_tilt_controller.launch
```
### 3.4 Start the listener 
parameter ist the degrees per message parameter (here 10 degrees per step)
```
rosrun scanner_dynamixel_control dxl_control 10
```
### 3.3 Execute the turns
The motor will respond to service calls. First time it will reset to zero position. From there it will move in the above given steps. Execute in a new terminal.
```
rosservice call /dxl_control/move

```

## 4. Settings
In case the table does not operate as expected due to changes of the system over
time there are several things that could fix the issue.
### 4.1 Hardware
Due to PID controlled movements its possible that the screws will get loosen
over time. To fix first unscrew the upper wooden plate then tighten the four
screws below. Do not fasten them to much, since this will increase resistance of
the ball bearing.
### 4.2 Software
In the file scanner_dynamixel_control/tilt.yaml there are four parameters you
might change depending on your requirements.
* joint_speed: sets the speed.
* joint_compliance_slope: P value of the PID controller.
* joint_compliance_punch: can be seen as a baseline that is added to the P value.
* joint_compliance_margin: defines the error between target and actual
value before the motor will start to act.
