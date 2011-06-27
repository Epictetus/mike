#include <list>
#include "html/HtmlPage.h"
#include "utils/Helpers.h"
#include "Frame.h"

namespace mike
{
  HtmlPage::HtmlPage(Request* request)
    : XmlPage(request)
  {
    type_ = HTML_PAGE;
  }

  XmlElementSet* HtmlPage::getElementsByCss(string rule)
  {
    // TODO: implement this someday...
    throw "HtmlPage::getElementsByCss is not implemented yet.";
  }

  XmlElementSet* HtmlPage::getElementsByClassName(string klass)
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
    return getElementByXpath(xpath);
  }
  
  XmlElement* HtmlPage::getElementById(string id)
  {
    id = xpathSanitize(id);
    return getElementByXpath("//*[@id='" + id + "'][1]");
  }
  
  XmlElementSet* HtmlPage::getFrames()
  {
    return getElementsByXpath("//iframe | //frameset/frame");
  }

  void HtmlPage::parseDocument()
  {
    xmlChar* body = xmlCharStrdup(getResponse()->getBody().c_str());
    doc_ = htmlParseDoc(body, NULL);
    xmlFree(body);
  }

  void HtmlPage::reload()
  {
    Page::reload();
    loadFrames();
  }
  
  void HtmlPage::openInFrame(Frame* frame)
  {
    Page::openInFrame(frame);
    loadFrames();
  }

  void HtmlPage::loadFrames()
  {
    if (frame_) {
      frame_->cleanup();
      
      XmlElementSet* frames = getFrames();

      for (vector<XmlElement*>::iterator it = frames->begin(); it != frames->end(); it++) {
	XmlElement* iframe = *it;

	if (iframe->hasAttribute("src")) {
	  http::Request* irequest = http::Request::Get(iframe->getAttribute("src"));
	  Page* ipage = Page::Build(irequest);
	  Frame* new_frame = frame_->buildFrame();

	  if (iframe->hasAttribute("name")) {
	    new_frame->setName(iframe->getAttribute("name"));
	  }
	
	  if (ipage->isHtml()) {
	    ipage->toHtmlPage()->openInFrame(new_frame);
	  } else {
	    ipage->openInFrame(new_frame);
	  }
	}
      }

      delete frames;
    }
  }
}
