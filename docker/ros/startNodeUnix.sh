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
-v /home/gentijo/Projects/ros/robo-truck/rosdev_ws:/opt/ros/rosdev_ws/ \
rosimg bash
