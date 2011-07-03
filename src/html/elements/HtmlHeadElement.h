#ifndef _MIKE_HTML_HEAD_ELEMENT_H_
#define _MIKE_HTML_HEAD_ELEMENT_H_

#include "html/HtmlAttrs.h"

namespace mike
{
  HTML_ELEMENT(Head) , WITH_ATTRS(I18n)
  {
  public:
    REGISTER_HTML_ELEMENT(Head);

    HTML_ATTRIBUTE(Id, "id");
    HTML_ATTRIBUTE(Profile, "profile");
  };
}

#endif /* _MIKE_HTML_HEAD_ELEMENT_H_ */
