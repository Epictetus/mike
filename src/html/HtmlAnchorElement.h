#ifndef _MIKE_HTML_ANCHOR_ELEMENT_H_
#define _MIKE_HTML_ANCHOR_ELEMENT_H_

#include "HtmlElement.h"

namespace mike
{
  class HtmlAnchorElement : public HtmlElement
  {
  public:
    HtmlAnchorElement(HtmlPage* page, xmlNodePtr node);
    virtual bool click();
  };
}

#endif /* _MIKE_HTML_ANCHOR_ELEMENT_H_ */
