#ifndef _MIKE_HTML_ATTRIBUTES_H_
#define _MIKE_HTML_ATTRIBUTES_H_

#include <string>
#include <vector>
#include "html/HtmlElement.h"

#define HTML_ATTRIBUTE(func, attr)			\
  string get##func()					\
  {							\
    return self()->getAttribute(attr);			\
  }							\
  bool has##func()					\
  {							\
    return self()->hasAttribute(attr);			\
  }							\
  bool has##func(string val)				\
  {							\
    return self()->hasAttribute(attr, val);		\
  }

namespace mike
{
  using namespace std;

  class HtmlElementWithAttrs
  {
  public:
    virtual HtmlElement* self() { return 0; }
  };
  
  class HtmlElementWithCoreAttrs : public virtual HtmlElementWithAttrs
  {
  public:
    HTML_ATTRIBUTE(Id, "id");
    HTML_ATTRIBUTE(Style, "style");
    HTML_ATTRIBUTE(Title, "title");

    /**
     * \return Class atribute value.
     */
    string getClass();
    
    /**
     * \return All classes as a vector.
     */
    vector<string> getClasses();

    /**
     * \param klass Class to check.
     * \return Whether element contains given class.
     */
    bool hasClass();
    bool hasClass(string klass);

    /**
     * \param klass Classes to check.
     * \return Whether element contains all given classes.
     */
    bool hasClasses(int n_args, ...);

    /**
     * \param klass Classes to check.
     * \return Whether element contains any of given classes.
     */
    bool hasAnyClass(int n_args, ...);
  };

  class HtmlElementWithI18nAttrs : public virtual HtmlElementWithAttrs
  {
  public:
    HTML_ATTRIBUTE(Lang, "lang");
    HTML_ATTRIBUTE(XmlLang, "xml:lang");
    HTML_ATTRIBUTE(Dir, "dir");
  };

  class HtmlElementWithEventAttrs : public virtual HtmlElementWithAttrs
  {
  public:
    HTML_ATTRIBUTE(OnClick, "onclick");
    HTML_ATTRIBUTE(OnDblClick, "ondblclick");
    HTML_ATTRIBUTE(OnMouseDown, "onmousedown");
    HTML_ATTRIBUTE(OnMouseUp, "onmouseup");
    HTML_ATTRIBUTE(OnMouseOver, "onmouseover");
    HTML_ATTRIBUTE(OnMouseOut, "onmouseout");
    HTML_ATTRIBUTE(OnMouseMove, "onmousemove");
    HTML_ATTRIBUTE(OnKeyPress, "onkeypress");
    HTML_ATTRIBUTE(OnKeyDown, "onkeydown");
    HTML_ATTRIBUTE(OnKeyUp, "onkeyup");
  };

  class HtmlElementWithAccessAttrs : public virtual HtmlElementWithAttrs
  {
  public:
    HTML_ATTRIBUTE(Accesskey, "accesskey");
    HTML_ATTRIBUTE(TabIndex, "tabindex");
    HTML_ATTRIBUTE(OnFocus, "onfocus");
    HTML_ATTRIBUTE(OnBlur, "onblur");
  };

  class HtmlElementWithHAlignAttrs : public virtual HtmlElementWithAttrs
  {
  public:
    HTML_ATTRIBUTE(Align, "align");
    HTML_ATTRIBUTE(Char, "char");
    HTML_ATTRIBUTE(CharOff, "charoff");
  };

  class HtmlElementWithVAlignAttrs : public virtual HtmlElementWithAttrs
  {
  public:
    HTML_ATTRIBUTE(VAlign, "valign");
  };

  class HtmlElementWithDefaultAttrs
    : public virtual HtmlElementWithCoreAttrs
    , public virtual HtmlElementWithI18nAttrs
    , public virtual HtmlElementWithEventAttrs
  {
  };
}

#endif /* _MIKE_HTML_ATTRIBUTES_H_ */
