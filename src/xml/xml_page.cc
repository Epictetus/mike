#include "xml/xml_page.h"

namespace mike
{
  XmlPage::XmlPage(Request* request)
    : Page(request, XML_PAGE)
  {
  }
}
