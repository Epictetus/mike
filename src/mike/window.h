#ifndef _MIKE_WINDOW_H_
#define _MIKE_WINDOW_H_

#include <list>
#include <string>
#include "mike/frame.h"

#define UA_CHROME11 "Mozilla/5.0 (Memory; %s %s) Mike/%s (Mike, like Gecko) Chrome/11 Safari/534.24"
#define UA_FIREFOX4 "Mozilla/5.0 (Memory; %s %s) Mike/%s (Mike, like Gecko) Firefox/4"

using namespace std;

namespace mike
{
  class Frame;
  typedef Frame* pFrame;

  struct WindowOptions
  {
    bool cookieEnabled;
    bool javaEnabled;
    string language;
    string userAgentTpl;
    int windowWidth;
    int windowHeight;
    WindowOptions();
  };
  typedef WindowOptions* pWindowOptions;
  
  class Window
  {
  private:
    pWindowOptions options;
    pFrame frame;
  public:
    Window(WindowOptions opts);
    virtual ~Window();

    bool IsCookieEnabled();
    bool IsJavaEnabled();
    string Language();
    string UserAgent();
    int Width();
    int Height();
    
    void Browse(string url, string method="GET", list<string> headers=list<string>(), string postData="");

    void Resize(int w, int h);
    void ResizeX(int w);
    void ResizeY(int h);
  };
  typedef Window* pWindow;
}

#endif /* _MIKE_WINDOW_H_ */
