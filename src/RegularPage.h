#ifndef _MIKE_REGULAR_PAGE_
#define _MIKE_REGULAR_PAGE_

#include <string>
#include <sstream>
#include "Page.h"

namespace mike
{
  /**
   * Regular page representation. 
   *
   */
  class RegularPage : public Page
  {
  public:
    /**
     * Constructor.
     *
     */
    explicit RegularPage(Request* request);

    /**
     * Destructor.
     *
     */
    virtual ~RegularPage();

  };
}

#endif /* _MIKE_REGULAR_PAGE_ */
