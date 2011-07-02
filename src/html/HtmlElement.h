#ifndef _MIKE_HTML_ELEMENT_H_
#define _MIKE_HTML_ELEMENT_H_

#include <string>
#include <vector>
#include "xml/XmlElement.h"

namespace mike
{
  using namespace std;

  class HtmlPage;
  
  class HtmlElement : public XmlElement
  {
  public:
    explicit HtmlElement(HtmlPage* page, xmlNodePtr node);
    virtual ~HtmlElement();

    vector<string> getClasses();

    string getClass();
    string getId();
    string getStyle();
    string getTitle();
    string getLang();
    string getXmlLang();

    bool hasClass(string klass);
    bool hasClasses(string *klass, ...);
    bool hasAnyClass(string *klass, ...);
    bool hasId(string id);
  };
}

#endif /* _MIKE_HTML_ELEMENT_H_ */
