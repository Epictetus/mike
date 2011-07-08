#!/bin/sh
AUTOHEADER=true autoreconf -i || exit 1
./configure $@
