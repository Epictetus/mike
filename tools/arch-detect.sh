#!/bin/sh

if [ "$ARCH" != "" ]; then
    echo $ARCH
    exit 0
fi

arch=`uname -m`

if [ "$arch" == "x86_64" ]; then
    echo "x64"
else
    echo "ia32"
fi