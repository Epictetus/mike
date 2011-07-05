#include <list>
#include <string.h>
#include <libxml/uri.h>

#include "utils/Helpers.h"
#include "html/HtmlPage.h"
#include "Browser.h"
#include "Window.h"

namespace mike
{
  /////////////////////////////// CONSTS  //////////////////////////////////////

  // links/buttons xpaths
  static const string kLinkXpath = \
    "//a[text()='%L' or @id='%L' or @name='%L']";
  static const string kButtonXpath = \
    "//button[text()='%L' or @id='%L' or @name='%L']";
  static const string kInputButtonXpath = \
    "//input[@type='submit' or @type='reset' or @type='image' or @type='button'][@value='%L' or @id='%L' or @name='%L']";

  // form fields xpaths
  static const string kSelectFieldXpath = \
    "//select[@name='%L' or @id='%L' or @id=//label[text()='%L']/@for]";
  static const string kTextareaXpath = \
    "//textarea[@name='%L' or @id='%L' or @id=//label[text()='%L']/@for]";
  static const string kInputFieldXpath = \
    "//input[@type!='hidden' and @type!='reset' and @type!='submit' and @type!='image'][@name='%L' or @id='%L' or @id=//label[text()='%L']/@for]";

  // complex locators
  static const string kLinkLocators[] = {
    kLinkXpath
  };
  static const string kButtonLocators[] = {
    kInputButtonXpath,
    kButtonXpath
  };
  static const string kLinkOrButtonLocators[] = {
    kLinkXpath,
    kButtonXpath,
    kInputButtonXpath
  };
  static const string kFormFieldLocators[] = {
    kInputFieldXpath,
    kSelectFieldXpath,
    kTextareaXpath
  };
  
  /////////////////////////////// HELPERS //////////////////////////////////////

  string buildXpathForLocator(const string parts[], int size, string locator)
  {
    locator = xpathSanitize(locator);
    string result[size];
    
    for (int i = 0, pos = 0; i < size; i++) {
      result[i] = parts[i];
      
      while ((pos = result[i].find("%L")) > 0)
	result[i] = result[i].substr(0, pos) + locator + result[i].substr(pos+2);
    }

    return strjoin(result, size, " | ");
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
    type_ = kHtmlPage;
    eventHandler_ = new HtmlEventHandler(this);
    javaScriptHandler_ = new JavaScriptHandler(this);
  }

  HtmlPage::~HtmlPage()
  {
    delete eventHandler_;
    delete javaScriptHandler_;
    delete_all< vector<HtmlFrame*> >(&frames_);
  }

  //============================= ACCESS     ===================================
  
  vector<HtmlElement*> HtmlPage::getElementsByXpath(string xpath)
  {
    return vector_cast<XmlElement,HtmlElement>(XmlPage::getElementsByXpath(xpath));
  }

  HtmlElement* HtmlPage::getElementByXpath(string xpath)
  {
    return (HtmlElement*)XmlPage::getElementByXpath(xpath);
  }

  HtmlElement* HtmlPage::getElementByPath(string path)
  {
    return (HtmlElement*)XmlPage::getElementByPath(path);
  }

  vector<HtmlElement*> HtmlPage::getElementsByTagName(string tag)
  {
    return vector_cast<XmlElement,HtmlElement>(XmlPage::getElementsByTagName(tag));
  }
  
  vector<HtmlElement*> HtmlPage::getElementsByCss(string rule)
  {
    // TODO: implement this someday...
    throw "HtmlPage::getElementsByCss is not implemented yet.";
  }
  
  HtmlElement* HtmlPage::getElementByCss(string rule)
  {
    // TODO: ...
    throw "HtmlPage::getElementByCss is not implemented yet.";
  }

  vector<HtmlElement*> HtmlPage::getElementsByClassName(string klass)
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
    string xpath = buildXpathForLocator(kLinkOrButtonLocators, 3, locator);
    return getElementByXpath(xpath);
  }

  HtmlElement* HtmlPage::getLink(string locator)
  {
    string xpath = buildXpathForLocator(kLinkLocators, 1, locator);
    return getElementByXpath(xpath);
  }

  HtmlElement* HtmlPage::getButton(string locator)
  {
    string xpath = buildXpathForLocator(kButtonLocators, 2, locator);
    return getElementByXpath(xpath);
  }

  HtmlElement* HtmlPage::getField(string locator)
  {
    string xpath = buildXpathForLocator(kFormFieldLocators, 3, locator);
    return getElementByXpath(xpath);
  }

  HtmlElement* HtmlPage::getElement(LocatorType type, string locator)
  {
    switch (type) {
    case kByXpath:
      return getElementByXpath(locator);
    case kByCss:
      return getElementByCss(locator);
    case kById:
      return getElementById(locator);
    case kByPath:
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
      HtmlElement* title = getElementByXpath("//html/head/title");
      return  title->getContent();
    } catch (ElementNotFoundError err) {
      // nothing...
    }

    return "";
  }

  string HtmlPage::getTitleText()
  {
    return getTitle();
  }

  vector<HtmlFrame*>& HtmlPage::getFrames()
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

  string HtmlPage::evaluate(string script)
  {
    // TODO: replace 0 with eval line number
    return javaScriptHandler_->evaluate(script, "<eval>", 0);
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
    if (frame_ && frame_->getWindow()->getBrowser()->isJavaEnabled()) {
      removeNoScriptNodes();
      vector<HtmlElement*> scripts = getElementsByTagName("script");

      for (vector<HtmlElement*>::iterator it = scripts.begin(); it != scripts.end(); it++) {
	HtmlElement* script = *it;
	bool is_javascript = script->hasAttribute("type", "text/javascript") || !script->hasAttribute("type");

	if (is_javascript) {
	  string content, filename;
	  unsigned int line = 0;
	  
	  if (script->hasAttribute("src")) {
	    filename = buildUri(script->getAttribute("src"), getUrl());

	    if (!loadAsset(filename, &content)) {
	      // TODO: debug info...
	      continue;
	    }
	  } else {
	    filename = getUrl();
	    content = script->getContent();
	    line = xmlGetLineNo(script->node_);
	  }
	    
	  javaScriptHandler_->evaluate(content, filename, line);
	} else {
	  // Unknown script error or debug info?...
	}
      }
    }
  }

  bool HtmlPage::loadAsset(string uri, string* content)
  {
    try {
      Browser* browser = frame_->getWindow()->getBrowser();
      Page* asset = Page::Open(uri, browser->isCookieEnabled(), browser->getSessionToken(), true);
      *content = asset->getContent();
      delete asset;
      return true;
    } catch (ConnectionError err) {
      return false;
    }
  }

  void HtmlPage::removeNoScriptNodes()
  {
    vector<HtmlElement*> nodes = getElementsByTagName("noscript");

    for (vector<HtmlElement*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
      xmlNodePtr noscript = (*it)->node_;
      xmlNodePtr node = noscript->children;
      noscript->children = NULL;
      
      while (node) {
	xmlNodePtr tmp = node;
	node = node->next;
	xmlUnlinkNode(tmp);
	xmlFree(tmp);
      }
    }
  }
  
  // XXX: add infinity loop prevention for frames opening!
  void HtmlPage::loadFrames()
  {
    if (frame_) {
      delete_all< vector<HtmlFrame*> >(&frames_);
      
      vector<HtmlElement*> frames = getElementsByXpath("//iframe | //frameset//frame");
      Browser* browser = frame_->getWindow()->getBrowser();

      for (vector<HtmlElement*>::iterator it = frames.begin(); it != frames.end(); it++) {
	HtmlElement* elem = *it;
	
	if (elem->hasAttribute("src")) {
	  try {
	    string uri = buildUri(elem->getAttribute("src"), getUrl());
	    Page* page = Page::Open(uri, browser->isCookieEnabled(), browser->getSessionToken());

	    HtmlFrame* frame = new HtmlFrame(frame_);
	    frames_.push_back(frame);

	    if (elem->hasAttribute("name")) {
	      frame->setName(elem->getAttribute("name"));
	    }
	    
	    page->enclose((Frame*)frame);
	  } catch (ConnectionError err) {
	    // TODO: debug info...
	  }
	}
      }
    }
  }
}
