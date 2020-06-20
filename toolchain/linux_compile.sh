#!/bin/bash

PROJECT_ROOT=$(realpath $(dirname `realpath $0`)/..)
FLAG_DEBUG="-DDEFINE_DEBUG=OFF"
CMAKE_BUILD_TYPE="Release"

# Parse the received commands
while :; do
    case $1 in
        -c|--clean) FLAG_CLEAN="SET"            
        ;;
        -d|--debug) 
        FLAG_DEBUG="-DDEFINE_DEBUG=ON"
        CMAKE_BUILD_TYPE="Debug"            
        ;;
        *) break
    esac
    shift
done

# Cleanup the existing files
if [[ ! -z "$FLAG_CLEAN" ]]; then
    rm -rf $PROJECT_ROOT/bin $PROJECT_ROOT/build
fi

# Compile!
mkdir -p $PROJECT_ROOT/build
cd $PROJECT_ROOT/build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=$CMAKE_BUILD_TYPE -B. -H$PROJECT_ROOT $FLAG_DEBUG
make -j8