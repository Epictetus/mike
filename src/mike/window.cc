#include <stdio.h>
#include <string.h>
#include "mike/config.h"
#include "mike/window.h"

namespace mike
{
  // Window options.
  
  WindowOptions::WindowOptions()
    : javaEnabled(true),
      cookieEnabled(true),
      language("en-US"),
      userAgentTpl(UA_CHROME11),
      windowWidth(1280),
      windowHeight(1024)
  {
  }

  // Browser window stuff.
  
  Window::Window(WindowOptions opts)
  {
    options = new WindowOptions(opts);
    frame = new Frame(this, NULL);
  }

  Window::~Window()
  {
    delete frame;
  }

  // Accessors to window options.
  
  bool Window::IsJavaEnabled()
  {
    return options->javaEnabled;
  }

  bool Window::IsCookieEnabled()
  {
    return options->cookieEnabled;
  }

  string Window::Language()
  {
    return options->language;
  }
  
  string Window::UserAgent()
  {
    char *agentFmt = (char*)options->userAgentTpl.c_str();
    char agent[strlen(agentFmt)+strlen(OS_TYPE)+strlen(CPU_ARCH)+strlen(MIKE_VERSION)];
    sprintf(agent, agentFmt, OS_TYPE, CPU_ARCH, MIKE_VERSION);
    return string(agent);
  }

  int Window::Width()
  {
    return options->windowWidth;
  }

  int Window::Height()
  {
    return options->windowHeight;
  }

  // Browsing...

  void Window::Browse(string url)
  {
    frame->Go(url);
  }

  // Window manipulation...

  void Window::Resize(int w, int h)
  {
    ResizeX(w);
    ResizeY(h);
  }

  void Window::ResizeX(int w)
  {
    options->windowWidth = w;
  }

  void Window::ResizeY(int h)
  {
    options->windowHeight = h;
  }
}
