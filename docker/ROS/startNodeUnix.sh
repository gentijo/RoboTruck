NODENAME=$1
WORKSPACE=$2

docker run --privileged -it \
--name $NODENAME  \
-h $NODENAME \
--net=host \
--env DISPLAY=$DISPLAY \
--env XAUTHORITY=/root/.Xauthority \
-v $XAUTHORITY:/root/.Xauthority \
-v /tmp/.X11-unix:/tmp/.X11-unix \
rosimg2 bash

#-v /home/gentijo/Projects/ROS-Projects/tutorial_ws/src/ros_tutorials:/opt/ros/dev-ws/src/ros_tutorials \
