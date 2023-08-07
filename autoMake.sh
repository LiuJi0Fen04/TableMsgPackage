#!/bin/bash


cd build

if [ $? -ne 0 ];then
    # echo "> ${pwd}"
    exit 1
else
    echo "> Entered build"
fi
if [ ${pwd} | grep "build" ]; then
    rm -rf CMakeFiles
    rm -rf CMakeCache.txt
    rm -rf cmake_install.cmake
    rm -rf Makefile
fi

cmake .. && make -j12 && cpack

