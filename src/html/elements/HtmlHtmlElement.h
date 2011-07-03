#ifndef _MIKE_HTML_HTML_ELEMENT_H_
#define _MIKE_HTML_HTML_ELEMENT_H_

#include "html/HtmlAttrs.h"

namespace mike
{
  HTML_ELEMENT(Html) , WITH_ATTRS(I18n)
  {
  public:
    REGISTER_HTML_ELEMENT(Html);

    HTML_ATTRIBUTE(Id, "id");
    HTML_ATTRIBUTE(XmlNs, "xmlns");
  };
}

#endif /* _MIKE_HTML_HTML_ELEMENT_H_ */
