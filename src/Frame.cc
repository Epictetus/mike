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
    cleanup();
  }
  
  void Frame::cleanup()
  {
    for (vector<Frame*>::iterator it = frames_.begin(); it != frames_.end(); it++)
      delete *it;

    frames_.clear();
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

  string Frame::getName()
  {
    return name_;
  }

  void Frame::setName(string name)
  {
    name_ = name;
  }
  
  Frame* Frame::buildFrame()
  {
    Frame* frame = new Frame(window_);
    frames_.push_back(frame);
    return frame;
  }

  vector<Frame*> Frame::getFrames()
  {
    return frames_;
  }

  Frame* Frame::getFrame(int key)
  {
    return (key < frames_.size() ? frames_[key] : NULL);
  }

  Frame* Frame::getNamedFrame(string name)
  {
    for (vector<Frame*>::iterator it = frames_.begin(); it != frames_.end(); it++) {
      string iname = (*it)->getName();

      if (!iname.empty() && name == iname) {
	return (*it);
      }
    }

    return NULL;
  }

  string Frame::getContent()
  {
    Page* current = getCurrentPage();
    return current ? current->getContent() : "";
  }
}
