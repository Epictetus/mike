#ifndef _MIKE_XML_PAGE_H_
#define _MIKE_XML_PAGE_H_

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

#include <string>
#include <vector>

#include "RegularPage.h"
#include "xml/XmlElement.h"
#include "xml/XmlElementSet.h"

namespace mike
{
  /**
   * XML page representation. 
   *
   */
  class XmlPage : public RegularPage
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
     *   XmlElementSet items = page->getElementsByXpath("//ul[id='items']//li");
     * </code>
     *
     */
    XmlElementSet* getElementsByXpath(string xpath);

    /**
     * Acts almost the same as <code>getElementsByXpath</code> but returns only first
     * found element.
     *
     */
    XmlElement* getElementByXpath(string xpath);

    /**
     * Returns set of all elements with given tag name. Example:
     *
     * <code>
     *   XmlElementSet images = page->getElementsByTagName('img');
     * </code>
     *
     */
    XmlElementSet* getElementsByTagName(string tag);

    /**
     * @override
     *
     */
    virtual void reload();
    
  protected:
    /**
     * Parses current page content as XML or HTML document, and prepares whole
     * environment to work. 
     *
     */
    virtual void prepareDocument();

    /**
     * Runs libxml parser on current page content and creates libxml document,
     * appropriate for page type (XML or HTML).
     *
     */
    virtual void parseDocument();
    
    /**
     * Cleans up document object if necessary.
     *
     */
    virtual void cleanupDocument();

    xmlDocPtr doc_;
  };
}

#endif /* _MIKE_XML_PAGE_H_ */
