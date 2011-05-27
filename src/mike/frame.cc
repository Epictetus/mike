#include <stdlib.h>
#include "mike/frame.h"

namespace mike
{
  // Browser window frame.
  
  Frame::Frame(pWindow window, pFrame parent/*=NULL*/)
    : window(window),
      parent(parent)
  {
    history = new mike::History();
  }

  Frame::~Frame()
  {
    delete history;
  }

  pWindow Frame::Window()
  {
    return window;
  }

  pFrame Frame::Parent()
  {
    return parent;
  }

  pHistory Frame::History()
  {
    return history;
  }

  bool Frame::IsReady()
  {
    //for (FrameList::iterator it=frames.begin(); it != frames.end(); it++) {
    //  if (!(*it)->IsReady()) return false;
    //}
    return (history->Current() && history->Current()->IsLoaded());
  }

  string Frame::Url()
  {
    return history->Current() ? history->Current()->Url() : "about:blank";
  }

  string Frame::Content()
  {
    if (history->Current()) {
      return history->Current()->Body();
    } else {
      throw FrameNotReadyError();
    }
  }
  
  // Content manipulation.
  
  void Frame::Go(string url, string method/*="GET"*/, list<string> headers/*=()*/, string postData/*=""*/)
  {
    pPage page = new Page(this, url, method, headers, postData);
    history->Push(page);
  }

  // History manipulation and info.
  
  void Frame::Go(int distance)
  {
    history->Go(distance);
  }

  void Frame::GoBack()
  {
    history->Back();
  }

  void Frame::GoForward()
  {
    history->Forward();
  }
}
