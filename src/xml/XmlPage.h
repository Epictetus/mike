#ifndef _MIKE_XML_PAGE_H_
#define _MIKE_XML_PAGE_H_

#include <string>
#include <vector>

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

#include "Page.h"
#include "xml/XmlElement.h"
#include "utils/Pector.h"

namespace mike
{
  typedef Pector<XmlElement> XmlElementSet;
  
  /**
   * Error raised when there is no elements in document matching given conditions (like xpath,
   * id, etc..). 
   */
  class ElementNotFoundError
  {
  public:
    ElementNotFoundError(string condition) : condition_(condition) {}
    const char* getReason() { return ("No element matches to a given conditions: " + condition_).c_str(); }
    const char* operator*() { return getReason(); }
  protected:
    string condition_;
  };

  /**
   * Error raised when invalid XPath expression is used to find element(s).
   */
  class InvalidXpathExpressionError
  {
  public:
    InvalidXpathExpressionError(string expr) : expr_(expr) {}
    const char* getReason() { return ("Invalid XPath expression: " + expr_).c_str(); }
    const char* operator*() { return getReason(); }
  protected:
    string expr_;
  };
  
  /**
   * LibXML2 powered XML page representation. This page type allows for XPath search,
   * and getting elements by tag names.
   */
  class XmlPage : public Page
  {
  public:
    explicit XmlPage(Request* request);
    virtual ~XmlPage();

    // override
    virtual void reload();
	
    /**
     * Looking for given xpath in and returns set of XML elements, If no element found then
     * empty set will be returned. 
     *
     * \code
     *   XmlElementSet* items = page->getElementsByXpath("//ul[id='items']//li");
     * \endcode
     *
     * \param xpath XPath expression.
     * \return Set of matching elements.
     */
    XmlElementSet* getElementsByXpath(string xpath);

    /**
     * Acts almost the same as <code>getElementsByXpath</code> but returns only first
     * found element. If none element matches given xpath then 'ElementNotFound' error
     * will be thrown.
     *
     * \param xpath XPath expression.
     * \return First matching element.
     */
    XmlElement* getElementByXpath(string xpath);

    /**
     * Returns set of elements with given tag name.
     *
     * \code
     *   XmlElementSet* images = page->getElementsByTagName('img');
     * \endcode
     *
     * \param tag Tag to find.
     * \return Elements matching requested tag.
     */
    XmlElementSet* getElementsByTagName(string tag);
    
  protected:
    xmlDocPtr doc_;

    /**
     * Parse current page content as XML document, and prepare environment
     * to work with. 
     */
    virtual void prepareDocument();

    /**
     * Runs libxml parser on current page content and creates libxml document,
     * appropriate for the XML page.
     */
    virtual void parseDocument();
    
    /**
     * Cleans up document object if necessary.
     */
    virtual void cleanupDocument();
  };
}

#endif /* _MIKE_XML_PAGE_H_ */
