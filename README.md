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

Mike uses autotools, so first you have to reconfigure your local copy:
  
    $ autoreconf -i
    $ ./configure

If you want to use different installation of V8 engine you can run configure with `--with-v8`
option:

    $ ./configure --with-v8=/absolute/path/to/v8

### Building V8

If you don't have installed v8 in your system then you can use development version
bundled in `deps/v8`. Mike provides target to build that local v8 version:

    $ make v8
    
### Compilation and testing

Making and cleaning up goes standard way. Running tests goes with `make test` command instead of
`make check` because we need to run few extra things before actual tests will start. 

    $ make
    $ make test
    $ make clean

### OSX Quirks

If youre a Mac user, you'll be probably very happy that you can play a little bit more
with some extra stuff to build Mike in development mode. If you're encountering problems
with your version of GNU m4, then you have to download and install exactly version 1.4.9,
and replace `gm4` binary (if exists): 

    sudo ln -sf /usr/local/bin/m4 /usr/bin/gm4

