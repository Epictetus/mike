#ifndef _MIKE_HTML_PAGE_H_
#define _MIKE_HTML_PAGE_H_

#include "page.h"
#include "xml/xml_page.h"

namespace mike
{
  /**
   * HTML page representation.
   *
   */
  class HtmlPage : public XmlPage
  {
  public:
    /**
     * Constructor.
     *
     */
    explicit HtmlPage(Request* request);
  };
}


#endif /* _MIKE_HTML_PAGE_H_ */
