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
    // XXX: i think it has to be done more complex...
    return getElementsByXpath("//*[contains(concat(' ', @class, ' '), ' " + klass + " ')]");
  }
  
  XmlElement* HtmlPage::getElementById(string id)
  {
    vector<XmlElement*> elems = getElementsByXpath("//*[@id='" + id + "'][1]");
    return elems.empty() ? NULL : elems[0];
  }

  void HtmlPage::parseDocument()
  {
    xmlChar* body = xmlCharStrdup(getResponse()->getBody().c_str());
    doc_ = htmlParseDoc(body, NULL);
  }
}
