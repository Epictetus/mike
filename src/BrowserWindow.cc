#include "http/Request.h"
#include "BrowserWindow.h"
#include "BrowserFrame.h"
#include "Page.h"

namespace mike
{
  BrowserWindow::BrowserWindow(Browser* browser, string url)
  {
    browser_ = browser;
    BrowserWindow(this, url);
  }

  BrowserWindow::BrowserWindow(BrowserWindow* parentWindow, string url)
  {
    browser_ = parentWindow->getBrowser();
    parentWindow_ = parentWindow;
    frame_ = new BrowserFrame(this);
    goTo(url);
  }

  BrowserWindow::~BrowserWindow()
  {
    delete frame_;
  }

  Browser* BrowserWindow::getBrowser()
  {
    return browser_;
  }

  BrowserWindow* BrowserWindow::getParentWindow()
  {
    return parentWindow_;
  }

  BrowserWindow* BrowserWindow::getTopLevelWindow()
  {
    BrowserWindow* top = parentWindow_;

    while (top != this) {
      top = top->getParentWindow();
    }

    return top;
  }

  BrowserFrame* BrowserWindow::getFrame()
  {
    return frame_;
  }

  Page* BrowserWindow::getPage()
  {
    return frame_->getCurrentPage();
  }

  string BrowserWindow::getUrl()
  {
    return frame_->getUrl();
  }

  void BrowserWindow::goTo(string url)
  {
    http::Request* request = http::Request::Get(url);
    Page* page = Page::Build(request);
    page->openInFrame(frame_);
  }
}
