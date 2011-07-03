#ifndef _MIKE_HTML_ELEMENT_H_
#define _MIKE_HTML_ELEMENT_H_

#include <string>
#include <vector>
#include "xml/XmlElement.h"
#include "html/HtmlAttributes.h"

namespace mike
{
  using namespace std;

  class HtmlPage;

  class HtmlElement : public XmlElement
  {
  public:
    explicit HtmlElement(HtmlPage* page, xmlNodePtr node);
    virtual ~HtmlElement();
  };
}

#endif /* _MIKE_HTML_ELEMENT_H_ */
