#include <stdlib.h>
#include "mike/history.h"

namespace mike
{
  History::History()
  {
  }
  
  History::~History()
  {
    back.push_back(current);
    back.clear();
    forward.clear();
  }

  pPage History::Current()
  {
    return current;
  }
  
  int History::Length()
  {
    return back.size()+forward.size();
  }

  void History::Push(pPage page)
  {
    if (current != NULL) {
      back.push_back(current);
    }

    forward.clear();
    current = page;
    current->Load();
  }

  void History::Back()
  {
    Go(-1);
  }

  void History::Forward()
  {
    Go(1);
  }
  
  void History::Go(int distance)
  {
    if (distance != 0) {
      pPage it;
      PageList *from = distance > 0 ? &forward : &back;
      PageList *to = distance < 0 ? &forward : &back;
    
      while ((*from).size() > 0 && abs(distance) > 0) {
	if (it) (*to).push_back(it);
	it = (*from).back();
	(*from).pop_back();
	distance--;
      }

      if (it) {
	current = it;
	current->Reload();
      }
    }
  }
}
