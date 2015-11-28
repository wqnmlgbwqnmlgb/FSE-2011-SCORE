#!/bin/bash

cd Desktop
sudo apt-get -y install git
sudo git clone https://github.com/SoftwareEngineeringToolDemos/FSE-2011-SCORE.git
cd FSE-2011-SCORE/build-vm/contents
sudo apt-get install flashplugin-installer
sudo chmod +x install.sh
sudo chmod -R a+rwx lock.sh

sudo cp install.sh ../../../install.sh

sudo cp SCORE.desktop ../../../SCORE.desktop

sudo cp lock.sh ../../../lock.sh

sudo cp SCORE.lock ../../../SCORE.lock



sudo mkdir "/home/vagrant/.config/autostart"
sudo cp SCORE.desktop /home/vagrant/.config/autostart/SCORE.desktop
sudo cp SCORE.lock /home/vagrant/.config/autostart/SCORE.lock


# Remove unnecessary launcher applications
sudo rm -f "/usr/share/applications/ubuntu-amazon-default.desktop"
sudo rm -f "/usr/share/applications/libreoffice-calc.desktop"
sudo rm -f "/usr/share/applications/libreoffice-writer.desktop"
sudo rm -f "/usr/share/applications/libreoffice-impress.desktop"
sudo rm -f "/usr/share/applications/ubuntu-software-center.desktop"


sudo reboot
