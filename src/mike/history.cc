#include <stdlib.h>
#include "mike/history.h"

namespace mike
{
  /**
   * Constructor.
   */
  History::History()
    : current(NULL)
  {
  }

  /**
   * Destructor.
   */
  History::~History()
  {
    back.push_back(current);
    back.clear();
    forward.clear();
  }

  /**
   * Returns currently browsed page.
   */
  pPage History::Current()
  {
    return current;
  }

  /**
   * Returns total number of pages stored in history. 
   */
  int History::Length()
  {
    return back.size()+forward.size();
  }

  /**
   * Loads given page and apends it to history list. At the same time it
   * clears forward pages stack.
   *
   * @param page: page to open
   */
  void History::Push(pPage page)
  {
    if (current != NULL) {
      back.push_back(current);
    }

    forward.clear();
    current = page;
    current->Load();
  }

  /**
   * Goes to previous page from history stack. 
   */
  void History::Back()
  {
    Go(-1);
  }

  /**
   * Goes to next page from history stack.
   */
  void History::Forward()
  {
    Go(1);
  }

  /**
   * Makes given number of steps through current history stack. When distance
   * is higher than 0 then goes forward, otherwise backward.
   *
   *   history->Go(10); // 10 pages forward
   *   history->Go(-2); // 2 pages backward
   *
   * @param distance: number of steps to go
   */
  void History::Go(int distance)
  {
    if (distance != 0) {
      pPage it;
      PageList *from = distance > 0 ? &forward : &back;
      PageList *to = distance < 0 ? &forward : &back;

      // TODO: there is definitelly some other, more efficient way to do this
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
