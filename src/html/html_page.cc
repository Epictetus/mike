#include "html/html_page.h"

namespace mike
{
  HtmlPage::HtmlPage(Request* request)
    : XmlPage(request)
  {
    type_ = HTML_PAGE;
  }
}
