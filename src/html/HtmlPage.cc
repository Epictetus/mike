#include <list>
#include <string.h>
#include <libxml/uri.h>

#include "utils/Helpers.h"
#include "html/HtmlPage.h"
#include "Browser.h"
#include "Window.h"

namespace mike
{
  // links/buttons locators
  const string XPATH_LINK_LOCATOR            = "//a[text()='%L' or @id='%L' or @name='%L']";
  const string XPATH_BUTTON_LOCATOR          = "//button[text()='%L' or @id='%L' or @name='%L']";
  const string XPATH_SUBMIT_OR_RESET_LOCATOR = "//input[@type='submit' or @type='reset'][@value='%L' or @id='%L' or @name='%L']";

  // form fields locators
  const string XPATH_INPUT_FIELD_LOCATOR     = "//input[@type!='hidden' and @type!='reset' and @type!='submit' and @type!='image'][@name='%L' or @id='%L' or @id=//label[text()='%L']/@for]";
  const string XPATH_SELECT_FIELD_LOCATOR    = "//select[@name='%L' or @id='%L' or @id=//label[text()='%L']/@for]";
  const string XPATH_TEXTAREA_LOCATOR        = "//textarea[@name='%L' or @id='%L' or @id=//label[text()='%L']/@for]";
  
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

  string buildUri(string uri, string base)
  {
    xmlChar* xuri = xmlCharStrdup(uri.c_str());
    xmlChar* xbase = xmlCharStrdup(base.c_str());
    xmlChar* xresult = xmlBuildURI(xuri, xbase);

    string result = (char*)xresult;

    xmlFree(xuri);
    xmlFree(xbase);
    xmlFree(xresult);

    return result;
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
    clearFrames();
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

  HtmlElement* HtmlPage::getElementByPath(string path)
  {
    return (HtmlElement*)XmlPage::getElementByPath(path);
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
  
  HtmlElement* HtmlPage::getElementByCss(string rule)
  {
    // TODO: ...
    throw "HtmlPage::getElementByCss is not implemented yet.";
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
    string locators[3] = { XPATH_INPUT_FIELD_LOCATOR, XPATH_SELECT_FIELD_LOCATOR, XPATH_TEXTAREA_LOCATOR };
    string xpath = buildXpathForLocator(locators, 3, locator);
    return getElementByXpath(xpath);
  }

  HtmlElement* HtmlPage::getElement(LocatorType type, string locator)
  {
    switch (type) {
    case BY_XPATH:
      return getElementByXpath(locator);
    case BY_CSS:
      return getElementByCss(locator);
    case BY_ID:
      return getElementById(locator);
    case BY_PATH:
      return getElementByPath(locator);
    }
  }
  
  HtmlElement* HtmlPage::getElement(string locator)
  {
    return getLinkOrButton(locator);
  }
  
  string HtmlPage::getTitle()
  {
    try {
      XmlElement* title = getElementByXpath("//html/head/title");

      if (title) {
	string text = title->getContent();
	delete title;
	return text;
      }
    } catch (ElementNotFoundError err) {
      // nothing...
    }

    return "";
  }

  string HtmlPage::getTitleText()
  {
    return getTitle();
  }

  vector<HtmlFrame*> HtmlPage::getFrames()
  {
    return frames_;
  }

  HtmlFrame* HtmlPage::getFrame(int n)
  {
    if (n < frames_.size()) {
      return frames_[n];
    } else {
      throw FrameNotExistsError();
    }
  }

  HtmlFrame* HtmlPage::getFrame(string name)
  {
    for (vector<HtmlFrame*>::iterator it = frames_.begin(); it != frames_.end(); it++) {
      if ((*it)->getName() == name) {
	return *it;
      }
    }

    throw NamedFrameNotExistsError(name);
  }

  HtmlFrame* HtmlPage::getNamedFrame(string name)
  {
    return getFrame(name);
  }

  //============================= OPERATIONS ===================================
  
  void HtmlPage::reload()
  {
    Page::reload();
    loadFrames();
    processScripts();
  }

  /////////////////////////////// PROTECTED ////////////////////////////////////

  void HtmlPage::enclose(Frame* frame)
  {
    Page::enclose(frame);
    loadFrames();
    processScripts();
  }

  void HtmlPage::parseDocument()
  {
    xmlChar* body = xmlCharStrdup(getResponse()->getBody().c_str());
    doc_ = htmlParseDoc(body, NULL);
    xmlFree(body);
  }

  void HtmlPage::processScripts()
  {
    if (frame_ && doc_) {
      if (frame_->getWindow()->getBrowser()->isJavaEnabled()) {
	removeNoScriptNodes();
	HtmlElementSet* scripts = getElementsByTagName("script");
      }
    }
  }

  void HtmlPage::removeNoScriptNodes()
  {
    HtmlElementSet* nodes = getElementsByTagName("noscript");

    for (vector<HtmlElement*>::iterator it = nodes->begin(); it != nodes->end(); it++)
      (*it)->unlink();
    
    delete nodes;
  }
  
  // XXX: add infinity loop prevention for frames opening!
  void HtmlPage::loadFrames()
  {
    clearFrames();

    if (frame_) {
      HtmlElementSet* frames = getElementsByXpath("//iframe | //frameset//frame");
      Browser* browser = frame_->getWindow()->getBrowser();

      for (vector<HtmlElement*>::iterator it = frames->begin(); it != frames->end(); it++) {
	HtmlElement* elem = *it;
	
	if (elem->hasAttribute("src")) {
	  string uri = buildUri(elem->getAttribute("src"), getUrl());
	  Request* request = Request::Get(uri);

	  if (browser->isCookieEnabled()) {
	    request->enableCookieSession(browser->getSessionToken());
	  }

	  try {
	    Page* page = Page::Factory(request);
	    HtmlFrame* frame = new HtmlFrame(frame_);
	    frames_.push_back(frame);

	    if (elem->hasAttribute("name")) {
	      frame->setName(elem->getAttribute("name"));
	    }
	    
	    page->enclose((Frame*)frame);
	  } catch (ConnectionError err) {
	    delete request;
	  }
	}
      }

      delete frames;
    }
  }

  void HtmlPage::clearFrames()
  {
    for (vector<HtmlFrame*>::iterator it = frames_.begin(); it != frames_.end(); it++) {
      delete *it;
      *it = NULL;
    }

    frames_.clear();
  }
}
