#!/bin/sh
autoconf -i && automake -i || exit 1
./configure $@
