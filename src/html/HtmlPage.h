#ifndef _MIKE_HTML_PAGE_H_
#define _MIKE_HTML_PAGE_H_

#include <string>
#include <vector>
#include "xml/XmlPage.h"

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

    /**
     * Works similar to <code>getElementsByXpath</code> method, only uses CSS selectors to
     * find elements.
     *
     * <code>
     *   vector<XmlElement*> items = page->getElementsByXpath("ul#items li");
     * </code>
     *
     */
    vector<XmlElement*> getElementsByCss(string selector);

    /**
     * Returns set of all elements having given class name.
     *
     * <code>
     *   vector<XmlElement*> tags = page->getElementsByClassName("tag");
     * </code>
     *
     */
    vector<XmlElement*> getElementsByClassName(string klass);

    /**
     * Returns first found element with given ID. If no elements found then <code>NULL</code>
     * will be returned. 
     *
     * <code>
     *   XmlElement* header = page->getElementById("header");
     * </code>
     *
     */
    XmlElement* getElementById(string id);
  };
}


#endif /* _MIKE_HTML_PAGE_H_ */
