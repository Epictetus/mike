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
    
    /**
     * Returns string stream with content of this page;
     *
     */
    stringstream* getStream();

    /**
     * Returns strinc content of this page.
     *
     */
    string getContent();
    
  };
}

#endif /* _MIKE_REGULAR_PAGE_ */
