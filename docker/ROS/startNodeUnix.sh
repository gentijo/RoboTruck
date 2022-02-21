NODENAME=$1
WORKSPACE=$2

docker run -it --privileged \
--name $NODENAME  \
-h $NODENAME \
--env DISPLAY=unix$DISPLAY \
-v $XAUTH:/root/.Xauthority \
-v /tmp/.X11-unix:/tmp/.X11-unix \
-v /home/gentijo/Projects/ROS-Projects/tutorial_ws/src/ros_tutorials:/opt/ros/dev-ws/src/ros_tutorials \
galactic-ros-base-xwin:latest
