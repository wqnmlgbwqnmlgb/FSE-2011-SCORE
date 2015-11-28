#!/bin/bash

cd Desktop
sudo apt-get -y install git
sudo git clone https://github.com/SoftwareEngineeringToolDemos/FSE-2011-SCORE.git
cd FSE-2011-SCORE/build-vm/contents
sudo cp install.sh ../../../install.sh
sudo cp SCORE.desktop ../../../SCORE.desktop

sudo mkdir "/home/vagrant/.config/autostart"
sudo cp Desktop/SCORE.desktop /home/vagrant/.config/autostart/SCORE.desktop


sudo reboot