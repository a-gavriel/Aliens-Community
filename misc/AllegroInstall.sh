#!/bin/bash

apt update
# The core library.
apt install liballegro5-dev
# The addons.
apt install liballegro-acodec5-dev liballegro-audio5-dev \
    liballegro-image5-dev liballegro-dialog5-dev liballegro-ttf5-dev \
    liballegro-physfs5-dev