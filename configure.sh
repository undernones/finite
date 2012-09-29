#!/usr/bin/env bash

if [ "$#" -lt 1 ]
then
    echo "Usage (case sensitive): $0 {Release|Debug}"
else
    cmake . -DCMAKE_BUILD_TYPE=$1
fi
