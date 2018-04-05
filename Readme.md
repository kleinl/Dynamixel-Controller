## 1. Software Installation

### 1.1 Install ROS(Tested with ROS Kinetic Kame):
http://wiki.ros.org/kinetic/Installation/Ubuntu
```
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
sudo apt-key adv --keyserver hkp://ha.pool.sks-keyservers.net:80 --recv-key 421C365BD9FF1F717815A3895523BAEEB01FA116
sudo apt-get update
sudo apt-get install ros-kinetic-ros-base
```
### 1.2 Set up ros environment
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
### 2.1 Connect the motor to a voltage source (red is plus, black minus) with 9-12V.
### 2.2 Plug in the usb2dynamixel stick to your notebook. (Communication slider set to TTL)
### 2.3 Connect the motor with the TTL port of the usb2dynamixel.

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
### 3.3 Start the tilt_controller in a new terminal
```
roslaunch scanner_dynamixel_control start_tilt_controller.launch
```
### 3.4 Start the listener with degrees per message parameter (here 10 degrees per step)
```
rosrun scanner_dynamixel_control talker 10
```
### 3.3 execute the turns in a new terminal repeatingly. First time it will reset to zero position.
```
topic pub -1 /chatter std_msgs/String "a"
```
