FROM ros:galactic-ros-base-focal

ENV TERM=xterm-color
ENV DEBIAN_FRONTEND=noninteractive

ENV LC_ALL C
ENV LANG en_US.UTF-8
ENV LANGUAGE en_US.UTF-8

ENV DISPLAY=host.docker.internal:0

COPY ./files/ros_entrypoint.sh /opt/ros
COPY ./files/ros_profile.sh /etc/profile.d
COPY ./files/init_micro_ros.sh /opt/ros

RUN apt update
RUN apt update

RUN apt -y upgrade

RUN apt install -y software-properties-common apt-transport-https
RUN apt install -y apt-utils
RUN apt install -y wget
RUN apt install -y emacs-nox
RUN apt install -y xterm
RUN apt install -y gnupg1
RUN apt install -y net-tools
RUN apt install -y iputils-ping
RUN apt install -y lighttpd
RUN apt install -y iproute2

RUN add-apt-repository ppa:mattrose/terminator
RUN apt update
RUN apt install -y terminator

RUN apt install -y ros-galactic-desktop
RUN rm -rf /var/lib/apt/lists/*

#RUN apt install -y python3-pip

RUN /opt/ros/ros_entrypoint.sh

# Create a workspace and download the micro-ROS tools
#RUN mkdir -p /opt/ros/microros_ws
#WORKDIR /opt/ros/microros_ws
#RUN git clone -b $ROS_DISTRO https://github.com/micro-ROS/micro_ros_setup.git src/micro_ros_setup

# Update dependencies using rosdep
#RUN sudo apt update && rosdep update
#RUN rosdep install --from-path src --ignore-src -y

#ENTRYPOINT ["/opt/ros/ros_entrypoint.sh"]
