#!/bin/bash

cd ~/engr101-avc
git pull
make || exit 1
