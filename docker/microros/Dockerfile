FROM ros:galactic-ros-base-focal

ENV TERM=xterm-color
ENV DEBIAN_FRONTEND=noninteractive

# install ros2 packages
RUN apt-get update
RUN apt-get install -y ros-galactic-desktop
RUN rm -rf /var/lib/apt/lists/*

ENV LC_ALL C
ENV LANG en_US.UTF-8
ENV LANGUAGE en_US.UTF-8

ENV DISPLAY=host.docker.internal:0
RUN apt-get install -y xterm

COPY ./files/ros_entrypoint.sh /
COPY ./files/ros_profile.sh /etc/profile.d

RUN apt update
RUN apt -y upgrade

RUN apt install -y terminator
RUN apt install -y wget gnupg2 software-properties-common apt-transport-https emacs

RUN useradd -s /bin/bash -m rosdev

RUN wget -qO- https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor > packages.microsoft.gpg
RUN install -o root -g root -m 644 packages.microsoft.gpg /etc/apt/trusted.gpg.d/
RUN sh -c 'echo "deb [arch=amd64,arm64,armhf signed-by=/etc/apt/trusted.gpg.d/packages.microsoft.gpg] https://packages.microsoft.com/repos/code stable main" > /etc/apt/sources.list.d/vscode.list'
RUN rm -f packages.microsoft.gpg
RUN apt update

RUN wget -q https://packages.microsoft.com/keys/microsoft.asc -O- | sudo apt-key add -
RUN add-apt-repository "deb [arch=amd64] https://packages.microsoft.com/repos/vscode stable main"
RUN apt update
RUN apt install -y code

# Source the ROS 2 installation
#RUN source /opt/ros/$ROS_DISTRO/setup.bash
RUN /ros_entrypoint.sh

# Create a workspace and download the micro-ROS tools
RUN mkdir -p /opt/ros/microros_ws
RUN cd /opt/ros/microros_ws
RUN git clone -b $ROS_DISTRO https://github.com/micro-ROS/micro_ros_setup.git src/micro_ros_setup

# Update dependencies using rosdep
RUN sudo apt update && rosdep update
RUN rosdep install --from-path src --ignore-src -y

# Install pip
RUN sudo apt-get install -y python3-pip

# Build micro-ROS tools and source them
#RUN colcon build
#RUN . install/local_setup.bash

ENTRYPOINT ["/ros_entrypoint.sh"]
