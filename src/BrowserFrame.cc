#include "BrowserFrame.h"

namespace mike
{
  BrowserFrame::BrowserFrame(BrowserWindow* window)
  {
    window_ = window_;
    history_ = new History();
  }

  BrowserFrame::~BrowserFrame()
  {
    delete history_;
  }

  string BrowserFrame::getUrl()
  {
    Page* current = history_->getCurrent();

    if (current != NULL) {
      return current->getUrl();
    } else {
      return "";
    }
  }
  
  Page* BrowserFrame::getCurrentPage()
  {
    return history_->getCurrent();
  }

  History* BrowserFrame::getHistory()
  {
    return history_;
  }

  BrowserWindow* BrowserFrame::getWindow()
  {
    return window_;
  }
}
