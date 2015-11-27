#!/bin/bash


sudo apt-get install git
git pull 
sudo apt-get install sshpass

sshpass -p vagrant ssh vagrant@vagrant DISPLAY=:0.0 gnome-terminal --working-directory=/home/vagrant/Desktop --title=irssi --command "./install.sh"sshpass -p vagrant ssh vagrant@vagrant DISPLAY=:0.0 xterm -hold -e " ./Desktop/install.sh; echo "hello""
