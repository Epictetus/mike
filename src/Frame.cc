#include "Frame.h"

namespace mike
{
  Frame::Frame(Window* window)
  {
    window_ = window_;
    history_ = new History();
  }

  Frame::~Frame()
  {
    delete history_;
  }

  string Frame::getUrl()
  {
    Page* current = history_->getCurrent();

    if (current != NULL) {
      return current->getUrl();
    } else {
      return "";
    }
  }
  
  Page* Frame::getCurrentPage()
  {
    return history_->getCurrent();
  }

  History* Frame::getHistory()
  {
    return history_;
  }

  Window* Frame::getWindow()
  {
    return window_;
  }
}
