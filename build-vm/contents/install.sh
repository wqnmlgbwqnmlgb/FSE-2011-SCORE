#!/bin/bash

cd Desktop
sudo rm -rf FSE-2011-SCORE
wget http://swtv.kaist.ac.kr/tools/score/SCORE-0.1.1

tar jxf SCORE-0.1.1


sudo apt-get install -y gcc-multilib
sudo apt-get install -y g++-multilib
sudo apt-get install -y ocaml

sudo apt-get install -y make

cd ../../../usr/lib/ocaml/

sudo ln -s libcamlstr.a libstr.a
cd ../../../
cd home/vagrant/
export PATH=/usr/lib:$PATH
export PATH=/usr/local/lib:$PATH

cd Desktop/SCORE-0.1.1/
export PATH=`pwd`/bin:$PATH

export LD_LIBRARY_PATH=`pwd`/lib

cd cil

make clean

./configure

make

cd ..
cd examples

../bin/scorec simple.c

cd ..

cd bin
./score_server -p 1000 &

cd ..
cd examples
../bin/score_client -i 10 -t ./simple -a 127.0.0.1 -p 1000 -o ./score-output

../bin/print_testcase score-output/testcase_4.test
cd 
cd Desktop
sudo rm -rf FSE-2011-SCORE
sudo rm -rf lock.sh
sudo rm -rf SCORE.desktop
sudo rm -rf SCORE.lock
