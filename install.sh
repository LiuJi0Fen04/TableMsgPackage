#!/bin/bash

# Cillian Young
# cd build

# note: this file should be in the same folder with package install script
# find if there is corresponed .sh and ./tar
type=".tar"
tar_find=$(find . -maxdepth 1 -type f -name "*"$type"*")

for a in $tar_find; do
    name="${a%%$type*}"
done

file_name=`echo $name | sed "s/^.\///"`".sh"

if [ -f $file_name ]; then

    chmod +x $file_name
    ./$file_name
    if [ $? -ne 0 ]; then
        echo "> Error: failed to extract file"
        exit 1
    else
        cd ./$name/config
        cgf_script=`find ./ -name "*Config.sh"`
        for a in $cgf_script; do
            chmod +x $a && $a
        done
        if [ $? -ne 0 ]; then
            echo "> Error: failed to config"
        else
            echo "> finished installation"
        fi
    fi
else
    echo "> Error: Can't find the file $file_name"    
fi

