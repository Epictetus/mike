#include "html/HtmlPage.h"

namespace mike
{
  HtmlPage::HtmlPage(Request* request)
    : XmlPage(request)
  {
    type_ = HTML_PAGE;
  }

  vector<XmlElement*> HtmlPage::getElementsByCss(string selector)
  {
    
  }

  vector<XmlElement*> HtmlPage::getElementsByClassName(string klass)
  {
    
  }
  
  XmlElement* HtmlPage::getElementById(string id)
  {
    
  }
}
