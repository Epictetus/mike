# Mike - The Headless Browser

This project is under development!

Mike is fully functional, extremaly fast web browser for testing purposes. Mike provides
JavaScript support powered by awesome V8 engine from Google.

## Dependencies

Before you start working with mike you have to install following dependencies (replace 
`apt-get install` with your favourite package manager's command).

Runtime dependencies:

    $ apt-get autotools scons libpcre libcurl libpthread

Development dependencies:
    
    $ apt-get install libcppunit-dev ruby
    $ gem install sinatra # used by dummy web app for testing

**NOTICE**: if you run the tests, and there is no results then you should read this file 
more carefouly... especially that 2 code lines above =P. Just install cppunit.

## Getting source

Clone repo and update submodules:

    $ git clone git@github.com/nu7hatch/mike
    $ git submodule init
    $ git submodule update

## Installing V8

Some distros (i.a. Arch Linux) provides `libv8` in repository. If your operating system doesn't
provide then you need to install one on your own, or used vendored version provided by mike in
`deps/vi` directory. 

    $ cd deps/v8
    $ scons library=static mode=release snapshot=off arch=XXX # arch can be either ia32 or x64

On some machines V8 may need extra parameters like `-fPIC` or `-fno-builtin-memcpy` flags. If
you encounter any problems then search V8 documentation for solutions.

## Running mike

Mike uses autotools, so first thing you have do is to reconfigure your local copy. You should use
our bundled script: 
  
    $ ./autogen.sh
    
**NOTICE**: Never use `autoreconf -i` implicitly. There are some custom config headers which shouldn't be 
recreated with autoheader! 

If you want to use custom build of V8, then you need to use `--with-v8` flag to tell where mike should
look it for:

    $ ./configure --with-v8=$(pwd)/deps/v8
    
**NOTICE**: You have to specify absolute path to V8 location.     
    
Making and cleaning up goes standard way. Running tests goes with `make test` command instead of
`make check` because we need to run few extra things before actual tests will start. That approach
was just easier than dealing with custom autotools stuff :).  

    $ make
    $ make test
    $ make clean

**TIP**: If you feel like make verbosity is to loud, you can pass `--enable-silent-rules` flag to 
`autogen.sh` or use `V` parameter in make:

    $ ./autogen.sh --enable-silent-rules
    $ make
    # make V=1 # verbose mode

## OSX Quirks

If youre a Mac user, you'll be probably very happy that you can play a little bit more
with some extra stuff to build Mike in development mode. If you're encountering problems
with your version of GNU m4, then you have to download and install exactly version 1.4.9,
and replace `gm4` binary (if exists): 

    sudo ln -sf /usr/local/bin/m4 /usr/bin/gm4
