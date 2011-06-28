#ifndef _MIKE_HTML_PAGE_H_
#define _MIKE_HTML_PAGE_H_

#include <libxml/HTMLparser.h>
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
     *   XmlElementSet* items = page->getElementsByXpath("ul#items li");
     * </code>
     *
     */
    XmlElementSet* getElementsByCss(string rule);

    /**
     * Returns set of all elements having given class name.
     *
     * <code>
     *   XmlElementSet* tags = page->getElementsByClassName("tag");
     * </code>
     *
     */
    XmlElementSet* getElementsByClassName(string klass);

    /**
     * Returns clicable element matched by it's anchor text/label. Applies only to <code>a</code>,
     * <code>button</code>, and <code>input[type=submit]</code> elements.
     *
     * <code>
     *   XmlElement* link = page->getElementByAnchor("Click me!");
     * </code> 
     *
     */
    XmlElement* getElementByAnchor(string content);

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

    /**
     * Returns all frames and iframes from this document.
     *
     */
    XmlElementSet* getFrames();

    string getTitle();
    
    /**
     * @override
     *
     */
    virtual void openInFrame(Frame* frame);

    /**
     * @override
     *
     */
    virtual void reload();
    
  protected:
    /**
     * @overriden
     *
     */
    virtual void parseDocument();

    /**
     * Loads are iframes and frames contents and opens it in current frame's subframes.
     *
     */
    virtual void loadFrames();

    htmlDocPtr doc_;
  };
}


#endif /* _MIKE_HTML_PAGE_H_ */
