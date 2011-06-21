#ifndef _MIKE_HISTORY_H_
#define _MIKE_HISTORY_H_

#include <list>
#include <string>
#include "Page.h"

namespace mike
{
  /**
   * History container for window frames. Each frame have it's own history.
   * All pages switching actions within frame should be handled by object of
   * this class.  
   *
   */
  class History
  {
  public:
    /**
     * Constructor.
     *
     */
    History();

    /**
     * Destructor.
     *
     */
    ~History();

    /**
     * Total number of elements in history container (back + forward).
     *
     */
    int size();

    /**
     * Returns pointer to current page. 
     *
     */
    Page* getCurrent();

    /**
     * Moves current page to back and sets given one as as current. 
     * At the same time it purges the forward pages container.
     *
     */
    void push(Page* page);

    /**
     * Moves current page to forward container and sets previous one as
     * current. 
     *
     */
    void goBack();

    /**
     * Moves current page to back container and sets next one as current.
     *
     */
    void goForward();

    /**
     * Jumps given number of pages back or forward and moves bunch of entries
     * from one container into another. 
     *
     */
    void go(int distance);

    /**
     * Reloads current page if it's possible.
     *
     */
    void reloadCurrent();
    
  protected:
    
    list<Page*> back_;
    list<Page*> forward_;
    Page* current_;
  };
}

#endif /* _MIKE_HISTORY_H_ */
