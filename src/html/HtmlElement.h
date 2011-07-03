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
  public:
    HtmlElement(HtmlPage* page, xmlNodePtr node);
    virtual ~HtmlElement();

    /**
     * Converts element to specified complex type. Original object will NOT be deleted
     * after this operation!
     *
     * \code
     *   HtmlElement elem = page->getElementByXpath("//div")
     *   HtmlDivElement* div = elem->cast<HtmlDivElement>();
     *   //...
     *   delete elem;
     *   delete div;
     * \endcode
     *
     * \return Element converted to specified type.
     */
    template <typename T> T* cast()
    {
      return new T((HtmlPage*)page_, node_);
    }

    /**
     * Acts similar to 'cast', but removes original object after conversion.
     *
     * \code
     *   HtmlDivElement* div;
     *   div = page->getElementByXpath("//div")->conv<HtmlDivElement>();
     *   //...
     *   delete div;
     * \endcode
     *
     * \return Element converted to specified type.
     */
    template <typename T> T* conv()
    {
      T* p = cast<T>();
      delete this;
      return p;
    }
  };
}

#endif /* _MIKE_HTML_ELEMENT_H_ */
