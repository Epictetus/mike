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

## Browser implementation

    * Window
      -> IsCookieEnabled
      -> IsJavaEnabled
      -> Language
      -> UserAgent
      -> Width
      -> Height
      -> Browse(url, options)
      -> Resize(w, h)
      -> ResizeX(w)
      -> ResizeY(h)

    * Frame
      -> Parent
      -> Window
      -> History
      -> Go(distance)
      -> Go(url, options)

    * Page
      -> Url
      -> Load
      -> Reload

    * HistoryContainer
      -> Length
      -> Current();
      -> Push(page)
      -> Go(distance)

## Javascript objects
    
    * History
      -> Length
      -> Back
      -> Forward
      -> Go(distance)

    * Navigator
      -> AppName
      -> AppVersion
      -> UserAgent
      -> Platform
      -> AppCodeName
      -> Product
      -> Vendor
      -> Language
      -> OnLine
      -> JavaEnabled
      -> CookieEnabled