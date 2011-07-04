#ifndef _MIKE_HISTORY_H_
#define _MIKE_HISTORY_H_

#include <list>
#include <string>

namespace mike
{
  using namespace std;
  
  class Page;
  
  /**
   * History container for window frames. Each frame have it's own history.
   * All pages switching actions within frame should be handled by object of
   * this class.  
   *
   * \code
   *   History* history = new History();
   *   history->push(page);
   *   assert(history->size() == 1);
   *   history->push(next_page);
   *   history->goBack();
   *   assert(history->getCurrent() == page);
   *   delete history;
   * \endcode
   */
  class History
  {
  public:
    /**
     * Creates instance of history container.
     */
    History();

    /**
     * Destructor.
     */
    ~History();

    /**
     * Total number of elements in history container (excluding current).
     *
     * \return History elements count.
     */
    int size();

    /**
     * \return Reference to current page. 
     */
    Page* getCurrent();

    /**
     * Moves current page to back and sets given one as a current. At the same time it
     * purges the forward pages container.
     *
     * \param page Page to set as current.
     */
    void push(Page* page);

    /**
     * Moves current page to forward container and sets previous one as current.
     */
    void goBack();

    /**
     * Moves current page to back container and sets next one as current.
     */
    void goForward();

    /**
     * Jumps given number of pages back or forward and moves bunch of entries from
     * one container into another. 
     */
    void go(int distance);

    
  protected:
    list<Page*> back_;
    list<Page*> forward_;
    Page* current_;

    /**
     * Reloads current page if it's possible.
     */
    void reloadCurrent();

  };
}

#endif /* _MIKE_HISTORY_H_ */
