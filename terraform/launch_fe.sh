#!/bin/bash

# Clone repo to home folder
cd && git clone https://github.com/herter4171/rfoutlet.git
cd rfoutlet/rf_frontend

# Launch Docker Compose in a Tmux session
tmux new-session -ds fe
tmux send-keys '$(which docker-compose) up' Enter
