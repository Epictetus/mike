#ifndef _MIKE_HISTORY_H_
#define _MIKE_HISTORY_H_

#include "mike/page.h"

namespace mike
{
  class History;
  class Page;
  
  typedef History* pHistory;
  typedef Page* pPage;
  typedef list<pPage> PageList;

  class History
  {
  private:
    PageList back;
    PageList forward;
    pPage current;
  public:
    History();
    virtual ~History();
    int Length();
    pPage Current();
    void Push(pPage page);
    void Back();
    void Forward();
    void Go(int distance);
  };
}

#endif /* _MIKE_HISTORY_H_ */
