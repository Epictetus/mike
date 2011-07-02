#include <list>
#include "html/HtmlPage.h"
#include "utils/Helpers.h"
#include "Frame.h"

namespace mike
{
  const string XPATH_LINK_LOCATOR = "//a[text()='%L' or @id='%L' or @name='%L']";
  const string XPATH_BUTTON_LOCATOR = "//button[text()='%L' or @id='%L' or @name='%L']";
  const string XPATH_SUBMIT_OR_RESET_LOCATOR = "//input[@type='submit' or @type='reset'][@value='%L' or @id='%L' or @name='%L']";
  const string XPATH_FORM_FIELD_LOCATOR = "";

  /////////////////////////////// HELPERS //////////////////////////////////////

  string buildXpathForLocator(string parts[], int size, string locator)
  {
    locator = xpathSanitize(locator);

    for (int i = 0, pos = 0; i < size; i++) {
      while ((pos = parts[i].find("%L")) > 0) {
	parts[i] = parts[i].substr(0, pos) + locator + parts[i].substr(pos+2);
      }
    }

    return strjoin(parts, size, " | ");
  }
  
  /////////////////////////////// PUBLIC ///////////////////////////////////////

  //============================= LIFECYCLE ====================================
  
  HtmlPage::HtmlPage(Request* request)
    : XmlPage(request)
  {
    type_ = HTML_PAGE;
  }

  HtmlPage::~HtmlPage()
  {
  }

  //============================= ACCESS     ===================================
  
  HtmlElementSet* HtmlPage::getElementsByXpath(string xpath)
  {
    return (HtmlElementSet*)XmlPage::getElementsByXpath(xpath);
  }

  HtmlElement* HtmlPage::getElementByXpath(string xpath)
  {
    return (HtmlElement*)XmlPage::getElementByXpath(xpath);
  }

  HtmlElementSet* HtmlPage::getElementsByTagName(string tag)
  {
    return (HtmlElementSet*)XmlPage::getElementsByTagName(tag);
  }
  
  HtmlElementSet* HtmlPage::getElementsByCss(string rule)
  {
    // TODO: implement this someday...
    throw "HtmlPage::getElementsByCss is not implemented yet.";
  }

  HtmlElementSet* HtmlPage::getElementsByClassName(string klass)
  {
    // TODO: write it without using xpath... we neeeed speeeeeed!
    klass = xpathSanitize(klass);
    return getElementsByXpath("//*[contains(concat(' ', @class, ' '), ' " + klass + " ')]");
  }
    
  HtmlElement* HtmlPage::getElementById(string id)
  {
    // TODO: the same as above, write without xpath!
    id = xpathSanitize(id);
    return getElementByXpath("//*[@id='" + id + "'][1]");
  }

  HtmlElement* HtmlPage::getLinkOrButton(string locator)
  {
    string locators[3] = { XPATH_LINK_LOCATOR, XPATH_BUTTON_LOCATOR, XPATH_SUBMIT_OR_RESET_LOCATOR };
    string xpath = buildXpathForLocator(locators, 3, locator);
    return getElementByXpath(xpath);
  }

  HtmlElement* HtmlPage::getLink(string locator)
  {
    string locators[1] = { XPATH_LINK_LOCATOR };
    string xpath = buildXpathForLocator(locators, 1, locator);
    return getElementByXpath(xpath);
  }

  HtmlElement* HtmlPage::getButton(string locator)
  {
    string locators[2] = { XPATH_BUTTON_LOCATOR, XPATH_SUBMIT_OR_RESET_LOCATOR };
    string xpath = buildXpathForLocator(locators, 2, locator);
    return getElementByXpath(xpath);
  }

  HtmlElement* HtmlPage::getField(string locator)
  {
    throw "Not implemented!";
  }
  
  string HtmlPage::getTitle()
  {
    XmlElement* dom_title = getElementByXpath("//html/head/title");

    if (dom_title) {
      string title = dom_title->getContent();
      delete dom_title;
      return title;
    }

    return "";
  }

  string HtmlPage::getTitleText()
  {
    return getTitle();
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
  
  void HtmlPage::enclose(Frame* frame)
  {
    Page::enclose(frame);
    loadFrames();
  }

  void HtmlPage::loadFrames()
  {
    if (frame_) {
      //XmlElementSet* frames = getFrames();

      /*
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
      */

      //delete frames;
    }
  }
}
