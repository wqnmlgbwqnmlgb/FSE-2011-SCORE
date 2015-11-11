#!/bin/bash

sudo bash
cd Desktop
echo ********* INSTALLING gcc packages **********
sudo apt-get install -y gcc-multilib
sudo apt-get install -y g++-multilib
echo ********* INSTALLING OCAML **********
sudo apt-get install -y ocaml
echo ********* INSTALLING make **********
sudo apt-get install -y make

cd ../../../usr/lib/ocaml/
echo ********* Setting symlinks **********
sudo ln -s libcamlstr.a libstr.a