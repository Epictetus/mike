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
    make check # runs tests suite

## OSX Quirks

On Macs you need to play a little bit with your version of GNU m4.
You have to download and install exactly version 1.4.9, and replace
`gm4` binary if exists: 

    sudo ln -sf /usr/local/bin/m4 /usr/bin/gm4

## Standard library

Internal standard library provided by mike is minimal as much as possible.
It provides the following stuff:

    File
      [c] read(path, modeloptions)
      [c] exists(path)
      [c] isFile(path)
      [c] isDirectory(path)
      [ ] join(path)
      [ ] absolute(path)
      [ ] directory(path)
      [ ] base(path)
    System
      [c] pwd()
      [c] cwd(dir)
    $stdout
      [c] write(text)
    $stderr
      [c] write(text)
    Thread
      [ ] spawn()
      [ ] kill(id)
      [ ] pid()
    Socket
      [ ] open(ip, port)
      [ ] write(data)
      [ ] read()
      [ ] close()
    global functions
      [ ] assert(value)
      [ ] require(file) 
      [ ] print(text, ...)
      [ ] puts(text, ...)
  