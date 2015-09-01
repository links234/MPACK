#!/bin/sh
#set -x

sudo apt-get install build-essential
sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
sudo apt-get update -qq
sudo apt-get install g++-4.7
sudo apt-get install libxxf86vm-dev
sudo apt-get install libgl1-mesa-dev libglu1-mesa-dev
sudo apt-get install libpng-dev
