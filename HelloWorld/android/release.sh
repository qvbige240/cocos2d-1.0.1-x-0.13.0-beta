#!/bin/bash
VERSION_NUM=1.0.1
source /etc/profile #Source file PATH, sometimes no NDK_ROOT defined.
LOG_FILE=`pwd`/log.txt
function mk_nativebuild()
{
    if [ x"$1" = x ]
    then
        echo "Native build: Not clean C/C++ libs"
    else
        echo "Native build: Clean C/C++ libs"
        rm -rf bin
        rm -rf obj
        rm -rf libs
        rm -rf gen
    fi
    bash build_native.sh
}

function mk_antbuild()
{
    ant clean > $LOG_FILE
    ant auto-release -Dversion=time >> $LOG_FILE
}
mk_nativebuild $1
mk_antbuild
