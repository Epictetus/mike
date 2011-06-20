#ifndef _MIKE_XML_PAGE_H_
#define _MIKE_XML_PAGE_H_

#include "page.h"

namespace mike
{
  /**
   * XML page representation. 
   *
   */
  class XmlPage : public Page
  {
  public:
    /**
     * Constructor.
     *
     */
    explicit XmlPage(Request* request);
  };
}


#endif /* _MIKE_XML_PAGE_H_ */
