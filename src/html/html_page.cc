#include "html/html_page.h"

namespace mike
{
  HtmlPage::HtmlPage(Request* request)
    : XmlPage(request)
  {
    type_ = HTML_PAGE;
  }

  XmlElementSet* HtmlPage::getElementsByCss(string selector)
  {
    
  }

  XmlElementSet* HtmlPage::getElementsByClassName(string klass)
  {
    
  }
  
  XmlElement* HtmlPage::getElementById(string id)
  {
    
  }
}
