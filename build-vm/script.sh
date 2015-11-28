#!/bin/bash

cd Desktop
sudo apt-get -y install git
sudo git clone https://github.com/SoftwareEngineeringToolDemos/FSE-2011-SCORE.git
cd FSE-2011-SCORE/build-vm/contents
sudo chmod +x install.sh
sudo cp install.sh ../../../install.sh

sudo cp SCORE.desktop ../../../SCORE.desktop

sudo mkdir "/home/vagrant/.config/autostart"
sudo cp SCORE.desktop /home/vagrant/.config/autostart/SCORE.desktop

# Remove unnecessary launcher applications
sudo rm -f "/usr/share/applications/ubuntu-amazon-default.desktop"
sudo rm -f "/usr/share/applications/libreoffice-calc.desktop"
sudo rm -f "/usr/share/applications/libreoffice-writer.desktop"
sudo rm -f "/usr/share/applications/libreoffice-impress.desktop"
sudo rm -f "/usr/share/applications/ubuntu-software-center.desktop"

# Disable screen lockout
mv /home/vagrant/Desktop/login_desktop.sh /home/vagrant/login_desktop.sh
sudo update-desktop-database
sudo cp /home/vagrant/Desktop/login_desktop.sh.desktop /etc/xdg/autostart/login_desktop.sh.desktop
rm /home/vagrant/Desktop/login_desktop.sh.desktop


sudo reboot
