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
-v /dev:/host-dev \
-v /home/gentijo/Projects/ros/robo-truck/microros_ws:/opt/ros/microros_ws \
microros bash

#-v /home/gentijo/Projects/ROS-Projects/tutorial_ws/src/ros_tutorials:/opt/ros/dev-ws/src/ros_tutorials \
