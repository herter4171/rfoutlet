#!/bin/bash

# Install Python, Docker, and misc.
amazon-linux-extras install python3 docker -y
yum install tmux git vim python3-pip -y

# Ensure Docker service will start
systemctl enable docker
systemctl start docker

# Ensure ec2-user has permissions to run Docker
usermod -aG docker ec2-user

# Install Docker Compose
curl -L "https://github.com/docker/compose/releases/download/1.25.0-rc2/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose
chmod +x /usr/local/bin/docker-compose
