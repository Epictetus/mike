#ifndef _MIKE_XML_ELEMENT_H_
#define _MIKE_XML_ELEMENT_H_

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <string>
#include <map>

namespace mike
{
  using namespace std;

  class XmlPage;
  class XmlElement;

  /**
   * This class represents single XML node element. It wraps up libxml2's <code>xmlNode</code>
   * and provides some extra functionalities at top of it.
   *
   */
  class XmlElement
  {
  public:
    /**
     * Constructor.
     *
     */
    explicit XmlElement(XmlPage* page, xmlNodePtr node);

    /**
     * Destructor.
     *
     */
    virtual ~XmlElement();

    /**
     * Returns value of specified attribute. If attribute is not defined then
     * empty string will be returned. 
     *
     */
    string getAttribute(string name);

    /**
     * Returns <code>true</code> when this node has specified attribute. If second parameter
     * specified then it checks if given value is the same as value of the checked attribute
     * (if this attr exists of course).
     *
     */
    bool hasAttribute(string name);
    bool hasAttribute(string name, string value);
    
    /**
     * Returns content of all children nodes.
     */
    string getContent();

    /**
     * When called without params then returns <code>true</code> if this elements contains any
     * content. If params passed then checks if it's the same as content of this element.
     *
     */
    bool hasContent();
    bool hasContent(string value);

    /**
     * Returns element's tag name.
     *
     */
    string getName();

    /**
     * Returns <code>true</code> when given element contains any children or text. So speaking
     * more accurately it happens only when current element is self closed.
     *
     */
    bool hasChildren();
    
  protected:
    XmlPage* page_;
    xmlNodePtr node_;
    map<string,xmlChar*> attrsCache_;
  };
}

#endif /* _MIKE_XML_ELEMENT_H_ */
