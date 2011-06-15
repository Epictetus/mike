# Mike - The Headless Browser

This project is under development!

Mike is fully functional, extremaly fast web browser for testing purposes. Mike provides
JavaScript support powered by awesome V8 engine from Google.

## Building development environment

Obviously first you have to install dependencies (replace `apt-get install` with your
package manager's command).

Runtime dependencies:

    $ apt-get install scons libpcre libcurl libpthread

Development dependencies:
    
    $ apt-get install cppunit ruby
    $ gem install sinatra # used by dummy web app for testing

### Preparation

We're using few external dependencies as git submodules so you have to do few extra steps
after first time clone:

    $ git clone git://github.com/nu7hatch/mike.git && cd mike
    $ git submodule init
    $ git submodule update

### Building V8

If you don't have installed v8 in your system then you can use development version
bundled in `deps/v8`. First you have to compile it:

    $ cd deps/v8 && make
    $ cd ../../
    
### Compilation and testing

Mike uses autotools, so first you have to reconfigure your local copy:
  
    $ autoreconf -i
    $ ./configure --with-v8=/absolute/path/to/v8/dir
    
The `--with-v8` flag is obsolete if you have V8 installed with `/usr/local` prefix.
Otherwise you have to specify full path to your V8 build. From now on you can use almost
standard set of make's targets:
    
    $ make
    $ make test
    $ make clean

Note: we're using `make test` instead of `make check` because running test suites
requires few extra dependencies to run befor actual tests execution.
    
### OSX Quirks

If youre a Mac user, you'll be probably very happy that you can play a little bit more
with some extra stuff to build Mike in development mode. If you're encountering problems
with your version of GNU m4, then you have to download and install exactly version 1.4.9,
and replace `gm4` binary (if exists): 

    sudo ln -sf /usr/local/bin/m4 /usr/bin/gm4

