#!/bin/bash

# Ensure image directories exist
mkdir -p images
ssh mac_mini 'mkdir -p ~/images'

# Take image
cd images
raspistill -w 1024 -h 768 -o $1.jpg

# Send to remote
scp $1.jpg mac_mini:~/images

