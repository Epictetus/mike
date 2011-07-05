#ifndef _MIKE_HTML_ELEMENT_H_
#define _MIKE_HTML_ELEMENT_H_

#include <string>
#include <vector>
#include "xml/XmlElement.h"

#define REGISTER_HTML_ELEMENT(type)				  	             \
  Html##type##Element(HtmlPage* page, xmlNodePtr node) : HtmlElement(page, node) {}; \
  virtual HtmlElement* self() { return (HtmlElement*)this; }

#define HTML_ELEMENT(type) \
  class Html##type##Element : public HtmlElement

#define WITH_ATTRS(group) \
  public Html##group##Attrs

#define HTML_ATTRIBUTE(func, attr)			\
  string get##func() { 					\
    return self()->getAttribute(attr);			\
  }							\
  bool has##func() {					\
    return self()->hasAttribute(attr);			\
  }							\
  bool has##func(string val) {				\
    return self()->hasAttribute(attr, val);		\
  }

namespace mike
{
  using namespace std;

  class HtmlPage;

  /**
   * Complex representation of HTML elements.
   */
  class HtmlElement : public XmlElement
  {
    friend class HtmlPage;
    
  public:
    HtmlElement(HtmlPage* page, xmlNodePtr node);
    virtual ~HtmlElement();

    /**
     * \return Whether element is a form field.
     */
    bool isField();

    /**
     * \return Whether element is a checkbox field.
     */
    bool isCheckBox();

    /**
     * \return Whether element is a radio field.
     */
    bool isRadio();
    
    /**
     * \return Whether element is a select field.
     */
    bool isSelect();

    /**
     * \return Whether element is a link.
     */
    bool isLink();

    /**
     * \return Whether element is a button.
     */
    bool isButton();

  };
}

#endif /* _MIKE_HTML_ELEMENT_H_ */
