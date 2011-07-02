#include "Browser.h"
#include "Window.h"
#include "Frame.h"
#include "Page.h"
#include "History.h"

namespace mike
{
  /////////////////////////////// PUBLIC ///////////////////////////////////////

  //============================= LIFECYCLE ====================================

  Frame::Frame()
  {
    history_ = new History();
  }
  
  Frame::Frame(Window* window)
  {
    window_ = window;
    history_ = new History();
  }

  Frame::Frame(Frame* parent)
  {
    window_ = parent->getWindow();
    history_ = new History();
  }
  
  Frame::~Frame()
  {
    delete history_;
  }

  //============================= ACCESS     ===================================
  
  void Frame::setPage(Page* page)
  {
    history_->push(page);
  }
  
  Page* Frame::getPage() const
  {
    return history_->getCurrent();
  }

  Page* Frame::getEnclosedPage() const
  {
    return getPage();
  }

  History* Frame::getHistory() const
  {
    return history_;
  }

  Window* Frame::getWindow() const
  {
    return window_;
  }

  Frame* Frame::getParent() const
  {
    return parent_;
  }

  void Frame::setName(string name)
  {
    name_ = name;
  }

  string Frame::getName() const
  {
    return name_;
  }
}
