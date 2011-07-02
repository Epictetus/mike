#include "Browser.h"
#include "Window.h"
#include "Frame.h"
#include "Page.h"
#include "html/HtmlPage.h"

namespace mike
{
  /////////////////////////////// PUBLIC ///////////////////////////////////////

  //============================= LIFECYCLE ====================================

  Window::Window(Browser* browser, int width/*=DEFAULT_WIDTH*/, int height/*=DEFAULT_HEIGHT*/)
  {
    init(width, height, this);
    browser_ = browser;
  }

  Window::Window(Window* parent, int width/*=DEFAULT_WIDTH*/, int height/*=DEFAULT_HEIGHT*/)
  {
    init(width, height, parent);
    browser_ = parent_->getBrowser();
  }

  Window::Window(int width, int height)
  {
    init(width, height, this);
  }
  
  Window::~Window()
  {
    delete frame_;
  }

  //============================= ACCESS     ===================================
  
  Browser* Window::getBrowser()
  {
    return browser_;
  }

  Window* Window::getParent()
  {
    return parent_;
  }

  Window* Window::getParentWindow()
  {
    return getParent();
  }

  Window* Window::getTopLevel()
  {
    Window* top = this;
    
    while (top != top->getParent()) {
      top = top->getParent();
    }
    
    return top;
  }

  Window* Window::getTopLevelWindow()
  {
    return getTopLevel();
  }

  void Window::setPage(Page* page)
  {
    page->enclose(frame_);
  }
  
  Page* Window::getPage()
  {
    return frame_->getPage();
  }

  string Window::getUrl()
  {
    return isBlank() ? "about:blank" : getPage()->getUrl();
  }

  bool Window::isBlank()
  {
    return frame_ == NULL || getPage() == NULL;
  }

  void Window::setWidth(int w)
  {
    resizeX(w);
  }

  int Window::getWidth()
  {
    return width_;
  }

  void Window::setHeight(int h)
  {
    resizeY(h);
  }

  int Window::getHeight()
  {
    return height_;
  }
  
  //============================= OPERATIONS ===================================
  
  void Window::close()
  {
    browser_->closeWindow(this);
  }

  void Window::resizeX(int w)
  {
    resize(w, height_);
  }

  void Window::resizeY(int h)
  {
    resize(width_, h);
  }

  void Window::resize(int w, int h)
  {
    // TODO: fire onresize event here.
    width_  = w;
    height_ = h;
  }
  
  /////////////////////////////// PROTECTED  ///////////////////////////////////
  
  void Window::init(int width, int height, Window* parent)
  {
    width_  = width;
    height_ = height;
    parent_ = parent;
    frame_  = new Frame(this);
  }

  /*
  void Window::goTo(string url)
  {
    if (!url.empty() && url != "about:blank") {
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
  */
}
