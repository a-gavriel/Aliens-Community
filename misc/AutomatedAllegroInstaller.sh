#!/bin/bash

apt install cmake

#Install Allegro Dependencies

apt install libx11-dev #X11 LIB
apt install libxcursor-dev #XCursos Lib
apt install libglu1-mesa-dev freeglut3-dev mesa-common-dev #OpenGL

#Donwload Allegro 
wget https://github.com/liballeg/allegro5/releases/download/5.2.6.0/allegro-5.2.6.0.tar.gz
#UnPack
tar -zxvf allegro-5.2.6.0.tar.gz

#Build and Install
cd ./allegro-5.2.6.0
mkdir build
cd build 
cmake ..
make -j4
make install -j4

#Set Allegro libs path to PKG_CONFIG_PATH
export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/usr/local/lib/pkgconfig

#Clean

cd ..
cd ..

rm -r  allegro-5.2.6.0
rm -r allegro-5.2.6.0.tar.gz