#ifndef _MIKE_XML_PAGE_H_
#define _MIKE_XML_PAGE_H_

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <string>

#include "page.h"
#include "xml/xml_element.h"
#include "xml/xml_element_set.h"

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

    /**
     * Destructor.
     *
     */
    virtual ~XmlPage();

    /**
     * Searches for given xpath in current document and returns set of XML elements,
     * If no element found then obviously empty set will be returned. 
     *
     * <code>
     *   XmlElementSet* items = page->getElementsByXpath("//ul[id='items']//li");
     * </code>
     *
     */
    XmlElementSet* getElementsByXpath(string xpath);

    /**
     * Returns set of all elements with given tag name. Example:
     *
     * <code>
     *   XmlElementSet* images = page->getElementsByTagName('img');
     * </code>
     *
     */
    XmlElementSet* getElementsByTagName(string tag);
    
  protected:
    /**
     * Parses current page content as XML or HTML document, and prepares whole
     * environment to work. 
     *
     */
    virtual void prepareDocument();
    
    /**
     * Cleans up document object if necessary.
     *
     */
    virtual void cleanupDocument();
    
    xmlDocPtr doc_;
  };
}

#endif /* _MIKE_XML_PAGE_H_ */
