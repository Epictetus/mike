#include <list>
#include "html/HtmlPage.h"

namespace mike {
  namespace
  {
    XmlElement* getFirstAndDropOthers(vector<XmlElement*> *elems)
    {
      if (!elems->empty()) {
	elems->resize(1);
	return elems->at(0);
	return NULL;
      } else {
	return NULL;
      }
    }
  }
  
  HtmlPage::HtmlPage(Request* request)
    : XmlPage(request)
  {
    type_ = HTML_PAGE;
  }

  vector<XmlElement*> HtmlPage::getElementsByCss(string rule)
  {
    // TODO: implement this someday...
    throw "HtmlPage::getElementsByCss is not implemented yet.";
  }

  vector<XmlElement*> HtmlPage::getElementsByClassName(string klass)
  {
    // XXX: i think it has to be done more complex...
    return getElementsByXpath("//*[contains(concat(' ', @class, ' '), ' " + klass + " ')]");
  }

  XmlElement* HtmlPage::getElementByAnchor(string content)
  {
    // XXX: sanitize content param!!!
    string match[3] = {
      "//a[.='" + content + "']",
      "//button[.='" + content + "']",
      "//input[@type='submit' or @type='reset' and @value='" + content + "']"
    };

    vector<XmlElement*> elems = getElementsByXpath(match[0] + "|" + match[1] + "|" + match[2]);
    return getFirstAndDropOthers(&elems);
  }
  
  XmlElement* HtmlPage::getElementById(string id)
  {
    vector<XmlElement*> elems = getElementsByXpath("//*[@id='" + id + "'][1]");
    return getFirstAndDropOthers(&elems);
  }

  void HtmlPage::parseDocument()
  {
    xmlChar* body = xmlCharStrdup(getResponse()->getBody().c_str());
    doc_ = htmlParseDoc(body, NULL);
  }
}
