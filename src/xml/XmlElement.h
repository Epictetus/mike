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
   * Single XML node representation. It wraps up libxml2's <code>xmlNode</code> and provides
   * extra functionalities at top of it.
   *
   * \code
   *   XmlElement* elem = page->getElementById("foobar");
   *   assert(elem->hasAttribute("class", "some-class"));
   *   assert(elem->hasContent("Foooo!");
   *   assert(elem->hasChildren());
   * \endcode
   */
  class XmlElement
  {
    friend class XmlPage;
    
  public:
    /**
     * Creates new element.
     *
     * \param page Page to which belongs this element.
     * \param node Wrapped libxml node.
     */
    XmlElement(XmlPage* page=NULL, xmlNodePtr node=NULL);

    /**
     * Destructor.
     */
    virtual ~XmlElement();

    /**
     * Returns value of specified attribute. If attribute is not defined then
     * empty string will be returned. 
     *
     * \param name Name of attribute.
     * \return Value of specified attribute.
     */
    virtual string getAttribute(string name);

    /**
     * Checks whether this node has defined given attribute or not. If second parameter
     * given then matches given value with attribute's value.
     *
     * \param name Name of attribute.
     * \param value Value to match.
     * \return Whether given attribute exists or equals specified value.
     */
    virtual bool hasAttribute(string name);
    virtual bool hasAttribute(string name, string value);
    
    /**
     * \return Content of all children nodes.
     */
    string getContent();
    string getText();

    /**
     * When called without params then checks whether this elements contains any text.
     * If param passed then matches it with the content of this element.
     *
     * \param value Value to match.
     * \retrurn Whether element contains any text, or contains specified text.
     */
    bool hasContent();
    bool hasContent(string value);
    bool hasText();
    bool hasText(string value);
    
    /**
     * \return Element's tag name.
     */
    string getTagName();

    /**
     * Returns whether given element contains any children/text or not. So speaking
     * more accurately returns false only when current element is self closed.
     *
     * \return Whether element has children nodes or not.
     */
    bool hasChildren();

    /**
     * \return XML path to this element.
     */
    string getPath();

    /**
     * \return XML source of this element. 
     */
    string toXml();
    string dump();
    
  protected:
    XmlPage* page_;
    xmlNodePtr node_;
  };
}

#endif /* _MIKE_XML_ELEMENT_H_ */
