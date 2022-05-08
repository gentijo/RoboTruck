NODENAME=$1
WORKSPACE=$2

docker run --privileged -it \
--name $NODENAME  \
-h $NODENAME \
--net=my-ipvlan2 \
--env DISPLAY=$DISPLAY \
--env XAUTHORITY=/root/.Xauthority \
-v $XAUTHORITY:/root/.Xauthority \
-v /tmp/.X11-unix:/tmp/.X11-unix \
microros bash

#-v /home/gentijo/Projects/ROS-Projects/tutorial_ws/src/ros_tutorials:/opt/ros/dev-ws/src/ros_tutorials \
