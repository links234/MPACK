#!/bin/sh
#set -x

sudo apt-get --yes --force-yes install build-essential
sudo -E add-apt-repository -y ppa:ubuntu-toolchain-r/test
sudo apt-get update -qq
sudo apt-get --yes --force-yes install g++-4.7
sudo apt-get --yes --force-yes install libxxf86vm-dev
sudo apt-get --yes --force-yes install libgl1-mesa-dev libglu1-mesa-dev
sudo apt-get --yes --force-yes install libpng-dev
