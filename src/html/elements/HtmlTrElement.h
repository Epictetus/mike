#ifndef _MIKE_HTML_TR_ELEMENT_H_
#define _MIKE_HTML_TR_ELEMENT_H_

#include "html/HtmlAttributes.h"

namespace mike
{
  HTML_ELEMENT(Tr)
    , WITH_ATTRS(Default)
    , WITH_ATTRS(HAlign)
    , WITH_ATTRS(VAlign)
  {
  public:
    REGISTER_HTML_ELEMENT(Tr);
  };
}

#endif /* _MIKE_HTML_TR_ELEMENT_H_ */
