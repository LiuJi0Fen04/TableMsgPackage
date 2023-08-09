#!/bin/bash

# Cillian Young
# note: this file should be in the same folder with CMakeLists.txt
# configuration

config_cmake()
{
    cd $1"_config"
    file="CMakeLists.txt"
    if [ ! -f  $file ]; then
        touch $file
        if [ $? -ne 0 ]; then
            echo "> Error: fail to generate $file"
            exit 1
        fi
    fi
    # "\\1" will result a backslash disappear, so we use "\\\1"
    echo -e 'cmake_minimum_required(VERSION 3.1.0)

project(CFG)
function(p_cut input num output)
    if(${num} EQUAL 2)
        string(REGEX REPLACE "(.*)/(.*)/(.*)" "\\\1" op  ${input})
        set(${output} ${op} PARENT_SCOPE)
    elseif(${num} EQUAL 1)
        string(REGEX REPLACE "(.*)/(.*)" "\\\1" op  ${input})
        set(${output} ${op} PARENT_SCOPE)
    else()
        message(STATUS "error param")
    endif()
endfunction()

p_cut(${CMAKE_CURRENT_SOURCE_DIR} 1 OUTPUT_PREFIX)

message(STATUS "> ${OUTPUT_PREFIX}")

# config your library
set('$1'_INCLUDE_DIRS ${OUTPUT_PREFIX}/include)
set('$1'_LIB_DIRS ${OUTPUT_PREFIX}/lib)
set('$1'_VERSION 1.0)
LINK_DIRECTORIES(${'$1'_LIB_DIRS})
set('$1'_LIB '$1')
configure_file('$1'Config.cmake.in ${OUTPUT_PREFIX}/lib/'$1'Config.cmake)' > $file
    echo "  $file generated"
    cd ..
}

config_script()
{
    cd $1"_config"
    file=$1"Config.sh"
    if [ ! -f  $file ]; then
        touch $file
        if [ $? -ne 0 ]; then
            echo "> Error: fail to generate $file"
            exit 1
        fi
    fi
    echo -e '#!/bin/bash
echo ""
echo ""
echo "> Being configured"
cmake .
echo ""
echo ""' > $file
    echo "  $file generated"
    cd ..
}

config_cmake_ini()
{
    cd $1"_config"
    file=$1"Config.cmake.in"
    if [ ! -f  $file ]; then
        touch $file
        if [ $? -ne 0 ]; then
            echo "> Error: fail to generate $file"
            exit 1
        fi
    fi
    echo -e "set("$1"_INCLUDE_DIRS @"$1"_INCLUDE_DIRS@)
set("$1"_LIB_DIRS @"$1"_LIB_DIRS@)
set("$1"_VERSION @"$1"_VERSION@)
LINK_DIRECTORIES(\${"$1"_LIB_DIRS})
set("$1"_LIB @"$1"_LIB@)" > $file
    echo "  $file generated"
    cd ..
}

pack_config()
{
    dir=$1"_config"
    if [ ! -d  $dir ]; then
        mkdir $dir
        if [ $? -ne 0 ]; then
            echo "> Error: fail to generate $dir"
            exit 1
        fi
        # config_script $dir
    fi
}



file_name="CMakeLists.txt"


pack_line=$(grep -i "include(CPack)" "$file_name")
line=$(grep -i "add_library(" "$file_name")
if echo $pack_line | grep "^include(CPack)" > /dev/null 2> /dev/null; then
    if_pack=1
    # TGT
    TGT=`echo $line | sed "s/^add_library(//"`
    TGT=${TGT%%\ *}
    echo "> TGT = ${TGT}"
    # generate a config
    echo "> Being configured"
    pack_config $TGT
    config_script $TGT
    config_cmake_ini $TGT
    config_cmake $TGT

    echo "> This build will generate an package"
else
    if_pack=0
    echo "> This is a normal build, without generatig an package"
fi


build="build"
if [ ! -d  $build ]; then
    mkdir $build
    if [ $? -ne 0 ]; then
        echo "> Error: fail to generate $build"
        exit 1
    fi
fi
cd $build

if [ $? -ne 0 ];then
    echo "> Error: build fail"
    exit 1
else
    echo "> Entered build"
fi
if echo $PWD | grep "build" > /dev/null 2> /dev/null; then
    echo "> building"
    cfg_dir=${TGT}"_config"
    rm -rf *
    cmake -DCFG_DIR=$cfg_dir ..    
    make -j12 
fi

if [[ $if_pack -eq 1 ]] && [[ $? -eq 0 ]]; then
    echo "> packing"    
    cpack
    cd ..
    rm -rf ${TGT}"_config"
fi

