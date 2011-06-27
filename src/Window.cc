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
    parentWindow_ = this;
    frame_ = new Frame(this);
    goTo(url);
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
    Window* top = this;

    while (top != top->getParentWindow()) {
      top = top->getParentWindow();
    };

    return top;
  }

  Frame* Window::getFrame()
  {
    return frame_;
  }

  Frame* Window::getFrame(int n)
  {
    return frame_->getFrame(n);
  }

  Page* Window::getPage()
  {
    return frame_->getCurrentPage();
  }

  string Window::getUrl()
  {
    return frame_->getUrl();
  }

  string Window::getContent()
  {
    return frame_->getContent();
  }

  string Window::getTitle()
  {
    if (!isBlank()) {
      if (getPage()->isHtml()) {
	XmlElement* title_tag = getPage()->toHtmlPage()->getElementByXpath("//html/head/title");

	if (title_tag) {
	  string title = title_tag->getContent();
	  delete title_tag;
	  return title;
	}
      }
      
      return getUrl();
    }

    return "Blank...";
  }

  Frame* Window::getNamedFrame(string name)
  {
    return frame_->getNamedFrame(name);
  }

  vector<Frame*> Window::getFrames()
  {
    return frame_->getFrames();
  }

  History* Window::getHistory()
  {
    return frame_->getHistory();
  }
  
  bool Window::isBlank()
  {
    return (frame_->getCurrentPage() == NULL);
  }

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
}
