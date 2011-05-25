#ifndef _MIKE_FRAME_H_
#define _MIKE_FRAME_H_

#include <string>
#include <list>
#include "mike/window.h"
#include "mike/history.h"
#include "mike/utils/http.h"

using namespace std;

namespace mike
{
  class Window;
  class Frame;
  class History;
  
  typedef Window* pWindow;
  typedef Frame* pFrame;
  typedef History* pHistory; 
  typedef list<pFrame> FrameList;
  
  class Frame
  {
  private:
    pFrame parent;
    pWindow window;
    FrameList frames;
    pHistory history;
  public:
    Frame(pWindow window, pFrame parent=NULL);
    virtual ~Frame();
    pFrame Parent();
    pWindow Window();
    pHistory History();
    void Go(string url);
    void Go(int distance);
    void GoBack();
    void GoForward();
  };
}

#endif /* _MIKE_FRAME_H_ */
