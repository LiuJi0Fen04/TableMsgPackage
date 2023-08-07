#!/bin/bash


cd TableMsg

./table_msg-1.0-Linux.sh

if [ $? -ne 0 ]; then
    echo ">Error: failed to extract file"
    exit 1
else
    cd ./table_msg-1.0-Linux/config
    chmod +x config.sh
    ./config.sh
    if [ $? -ne 0 ]; then
        echo ">Error: failed to config"
    else
        echo "> finished installation"
    fi
fi