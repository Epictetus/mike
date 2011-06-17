#!/bin/sh

arch=`uname -m`

if [ "$arch" == "x86_64" ]; then
    echo "x64"
else
    echo "ia32"
fi