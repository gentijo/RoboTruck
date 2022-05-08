/opt/ros/ros_entrypoint.sh

# Create a workspace and download the micro-ROS tools
#mkdir -p /opt/ros/microros_ws
cd /opt/ros/microros_ws
git clone -b $ROS_DISTRO https://github.com/micro-ROS/micro_ros_setup.git src/micro_ros_setup

# Update dependencies using rosdep
sudo apt update && rosdep update
rosdep install --from-path src --ignore-src -y

# Install pip
sudo apt-get install python3-pip

# Build micro-ROS tools and source them
colcon build
source install/local_setup.bash
