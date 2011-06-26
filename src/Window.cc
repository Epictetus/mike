#include "http/Request.h"
#include "Window.h"
#include "Frame.h"
#include "Page.h"
#include "RegularPage.h"
#include "xml/XmlPage.h"
#include "html/HtmlPage.h"

namespace mike
{
  Window::Window(Browser* browser, string url)
  {
    browser_ = browser;
    Window(this, url);
  }

  Window::Window(Window* parentWindow, string url)
  {
    browser_ = parentWindow->getBrowser();
    parentWindow_ = parentWindow;
    frame_ = new Frame(this);
    goTo(url);
  }

  Window::~Window()
  {
    delete frame_;
  }

  Browser* Window::getBrowser()
  {
    return browser_;
  }

  Window* Window::getParentWindow()
  {
    return parentWindow_;
  }

  Window* Window::getTopLevelWindow()
  {
    Window* top = parentWindow_;

    while (top != this) {
      top = top->getParentWindow();
    }

    return top;
  }

  Frame* Window::getFrame()
  {
    return frame_;
  }

  Page* Window::getPage()
  {
    return frame_->getCurrentPage();
  }

  string Window::getUrl()
  {
    return frame_->getUrl();
  }

  void Window::goTo(string url)
  {
    http::Request* request = http::Request::Get(url);

    if (browser_->isCookieEnabled()) {
      request->enableCookieSession(browser_->getSessionToken());
    }
      
    Page* page = Page::Build(request);

    if (page->isHtml()) {
      page->toHtmlPage()->openInFrame(frame_);
    } else {
      page->openInFrame(frame_);
    }
  }
}
