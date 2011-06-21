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
    explicit XmlElement(XmlPage* page, xmlNode* node);

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
     * Returns only text content of this node.
     *
     */
    string getText();

    /**
     * Returns whole content of this node (inner XML content).
     */
    string getContent();
    
  protected:
    XmlPage* page_;
    xmlNode* node_;
    map<string,xmlChar*> attrsCache_;
  };
}

#endif /* _MIKE_XML_ELEMENT_H_ */
