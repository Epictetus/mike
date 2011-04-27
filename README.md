# Building Mike

Dependencies first:

  apt-get install scons
  apt-get install libpcre
  apt-get install libcurl
  apt-get install libpthread
  apt-get install cppunit # only if you want to run tests

CoffeeScript compiler, eg:

  apt-get install nodejs
  npm install coffee-script

Building and testing:
  
  autoreconf -i
  ./configure
  make
  make check

## OSX Quirks

On Macs you need to play a little bit with your version of GNU m4.
You have to download and install exactly version 1.4.9, and replace
`gm4` binary if exists: 

  sudo ln -sf /usr/local/bin/m4 /usr/bin/gm4