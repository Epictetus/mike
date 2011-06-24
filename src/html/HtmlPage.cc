#include <list>
#include "html/HtmlPage.h"
#include "utils/Helpers.h"

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
    klass = xpathSanitize(klass);
    return getElementsByXpath("//*[contains(concat(' ', @class, ' '), ' " + klass + " ')]");
  }

  XmlElement* HtmlPage::getElementByAnchor(string content)
  {
    content = xpathSanitize(content);
    
    string parts[3] = {
      "//a[.='" + content + "']",
      "//button[.='" + content + "']",
      "//input[(@type='submit' or @type='reset') and @value='" + content + "']"
    };

    string xpath = parts[0] + "|" + parts[1] + "|" + parts[2];
    vector<XmlElement*> elems = getElementsByXpath(xpath);
    return getFirstAndDropOthers(&elems);
  }
  
  XmlElement* HtmlPage::getElementById(string id)
  {
    id = xpathSanitize(id);
    vector<XmlElement*> elems = getElementsByXpath("//*[@id='" + id + "'][1]");
    return getFirstAndDropOthers(&elems);
  }

  void HtmlPage::parseDocument()
  {
    xmlChar* body = xmlCharStrdup(getResponse()->getBody().c_str());
    doc_ = htmlParseDoc(body, NULL);
  }
}
