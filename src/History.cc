#include <stdlib.h>
#include "History.h"

namespace mike
{
  History::History()
  {
    current_ = NULL;
  }

  History::~History()
  {
    delete current_;
    back_.clear();
    forward_.clear();
  }

  Page* History::getCurrent()
  {
    return current_;
  }

  int History::size()
  {
    return back_.size() + forward_.size();
  }

  void History::push(Page* page)
  {
    if (current_) {
      back_.push_back(current_);
    }
    
    current_ = page;
    forward_.clear();
  }

  void History::goBack()
  {
    go(-1);
  }

  void History::goForward()
  {
    go(1);
  }

  void History::go(int distance)
  {
    if (distance != 0) {
      list<Page*>::iterator it;

      // Um, almost as ugly as predator, but equally fast... so don't mess with it
      // or it's gonna turn your skull into trophy! :]
      if (distance < 0) {
	if ((distance = abs(distance) <= back_.size() ? distance : -back_.size()) != 0) {
	  advance((it = back_.end()), distance+1);
	  forward_.push_front(current_);
	  forward_.splice(forward_.begin(), back_, it, back_.end());
	  current_ = back_.back();
	  back_.pop_back();
          reloadCurrent();
	}
      } else {
	if ((distance = distance <= forward_.size() ? distance : forward_.size()) != 0) {
	  advance((it = forward_.begin()), distance-1);
	  back_.push_back(current_);
	  back_.splice(back_.end(), forward_, forward_.begin(), it);
	  current_ = forward_.front();
	  forward_.pop_front();
          reloadCurrent();
	}
      }
    }
  }

  void History::reloadCurrent()
  {
    if (current_) {
      current_->reload();
    }
  }
}
