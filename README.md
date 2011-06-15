# Building Mike

Dependencies first:

    apt-get install scons libpcre libcurl libpthread
    apt-get install cppunit # only if you want to run tests

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
      -> Browse(url, method, headers, postData)
      -> IsReady
      -> Url
      -> Content
      -> Resize(w, h)
      -> ResizeX(w)
      -> ResizeY(h)

    * Frame
      -> Parent
      -> Window
      -> History
      -> IsReady
      -> Url
      -> Content
      -> Go(distance)
      -> Go(url, method, headers, postData)
      -> GoBack
      -> GoForward
      
    * Page
      -> Url
      -> Load
      -> Reload
      -> IsLoaded
      -> Body
      -> Request
      -> Response
      -> Document

    * History
      -> Length
      -> Current
      -> Push(page)
      -> Go(distance)
      -> Back
      -> Forward