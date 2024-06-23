#!/bin/bash

sudo apt update && sudo apt upgrade -y
sudo apt install -y git build-essential cmake python3-dev python3-pip python3-venv zsh curl wget vim tmux htop tree unzip zip tldr

# Install Oh My Zsh
sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

# ZSH_THEME="tjkirch" is prefered

# Install auto-suggestions plugin
git clone https://github.com/zsh-users/zsh-autosuggestions ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-autosuggestions

