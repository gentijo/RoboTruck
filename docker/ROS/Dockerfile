FROM ros:galactic-ros-base-focal

# install ros2 packages
RUN apt-get update
RUN apt-get install -y ros-galactic-desktop
RUN rm -rf /var/lib/apt/lists/*

ENV DISPLAY=host.docker.internal:0
RUN sudo apt-get install -y xterm

COPY ./ros_entrypoint.sh /

RUN sudo apt install -y wget
RUN wget -qO- https://packages.microsoft.com/keys/microsoft.asc | gpg --dearmor > packages.microsoft.gpg
RUN sudo install -o root -g root -m 644 packages.microsoft.gpg /etc/apt/trusted.gpg.d/
RUN sudo sh -c 'echo "deb [arch=amd64,arm64,armhf signed-by=/etc/apt/trusted.gpg.d/packages.microsoft.gpg] https://packages.microsoft.com/repos/code stable main" > /etc/apt/sources.list.d/vscode.list'
RUN rm -f packages.microsoft.gpg
RUN sudo apt install -y apt-transport-https
RUN sudo apt update
RUN sudo apt install -y code

ENTRYPOINT ["/ros_entrypoint.sh"]
