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
     * Returns <code>true</code> when this node has specified attribute.
     *
     */
    bool hasAttribute(string name);
    
    /**
     * Returns content of all children nodes.
     */
    string getContent();
    
  protected:
    XmlPage* page_;
    xmlNodePtr node_;
    map<string,xmlChar*> attrsCache_;
  };
}

#endif /* _MIKE_XML_ELEMENT_H_ */
