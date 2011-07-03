#ifndef _MIKE_HTML_DIV_ELEMENT_H_
#define _MIKE_HTML_DIV_ELEMENT_H_

#include "html/HtmlAttributes.h"

namespace mike
{
  HTML_ELEMENT(Div) , WITH_ATTRS(Default)
  {
  public:
    REGISTER_HTML_ELEMENT(Div);
  };
}

#endif /* _MIKE_HTML_DIV_ELEMENT_H_ */
