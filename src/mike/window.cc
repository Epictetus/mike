#include <stdio.h>
#include <string.h>
#include "mike/config.h"
#include "mike/window.h"

namespace mike
{
  /**
   * WindowOptions constructor.
   */
  WindowOptions::WindowOptions()
    : javaEnabled(true),
      cookieEnabled(true),
      language("en-US"),
      userAgentTpl(UA_CHROME11),
      windowWidth(1280),
      windowHeight(1024)
  {
  }

  /**
   * Window constructor. Creates window with specified options. See the
   * <code>WindowOptions</code> struct to get know what opts are available. 
   *
   * @param opts: window options
   */
  Window::Window(WindowOptions opts)
  {
    options = new WindowOptions(opts);
    frame = new Frame(this, NULL);
  }

  /**
   * Window destructor.
   */
  Window::~Window()
  {
    delete frame;
  }

  /**
   * Returns <code>true</code> when this window allows for JavaScript code
   * execution.
   */
  bool Window::IsJavaEnabled()
  {
    return options->javaEnabled;
  }

  /**
   * Returns <code>true</code> when this window allows for storing cookies.
   */
  bool Window::IsCookieEnabled()
  {
    return options->cookieEnabled;
  }

  /**
   * Returns window (user) language. This language may be used in headers
   * for page requests.
   */
  string Window::Language()
  {
    return options->language;
  }

  /**
   * Returns simulated user agent string, based on current operating system,
   * architecture and mike's version. User agent can simulate Friefox or Chrome,
   * but can't simulate architecture, operating system etc. 
   */
  string Window::UserAgent()
  {
    char *agentFmt = (char*)options->userAgentTpl.c_str();
    char agent[strlen(agentFmt)+strlen(OS_TYPE)+strlen(CPU_ARCH)+strlen(MIKE_VERSION)];
    sprintf(agent, agentFmt, OS_TYPE, CPU_ARCH, MIKE_VERSION);
    return string(agent);
  }

  /**
   * Returns configured window width.
   */
  int Window::Width()
  {
    return options->windowWidth;
  }

  /**
   * Returns configure window height.
   */
  int Window::Height()
  {
    return options->windowHeight;
  }

  /**
   * Generates request based on specified options and loads page to browser's main
   * frame. Here your'e able to specify request method (only GET and POST are supported),
   * custom headers, and post fields data. Here's the simplest example:
   *
   *   mike::WindowOptions opts;
   *   mike::pWindow window = new mike::Window(opts);
   *   window->Browse("http://www.mypage.com");
   *
   * TODO: support for multipart requests
   *
   * @param url: address of visited website
   * @param method: request method
   * @param headers: list with request headers
   * @param postData: post fields data
   */
  void Window::Browse(string url, string method/*="GET"*/, list<string> headers/*=()*/, string postData/*=""*/)
  {
    frame->Go(url, method, headers, postData);
  }

  /**
   * Returns <code>true</code> when page (and all frames) has been properly loaded. 
   */
  bool Window::IsReady()
  {
    return frame->IsReady();
  }

  /**
   * Returns url address of currently browsed page.
   */
  string Window::Url()
  {
    return frame->Url();
  }

  /**
   * Returns contents of current website if loaded. If not, throws error.
   */
  string Window::Content()
  {
    return frame->Content();
  }
  
  /**
   * Changes window size to specified values.
   *
   * @param w: new width
   * @param h: new height
   */
  void Window::Resize(int w, int h)
  {
    ResizeX(w);
    ResizeY(h);
  }

  /**
   * Resizes window horizontaly. 
   *
   * @param w: new width
   */
  void Window::ResizeX(int w)
  {
    options->windowWidth = w;
  }

  /**
   * Resizes window verticaly.
   *
   * @param h: new height
   */
  void Window::ResizeY(int h)
  {
    options->windowHeight = h;
  }
}
