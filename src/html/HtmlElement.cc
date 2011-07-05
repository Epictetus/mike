#include "utils/Helpers.h"
#include "html/HtmlElement.h"
#include "html/HtmlPage.h"
#include "Window.h"
#include "Frame.h"
#include "Browser.h"

namespace mike
{
  /////////////////////////////// PUBLIC ///////////////////////////////////////

  //============================= LIFECYCLE ====================================
  
  HtmlElement::HtmlElement(HtmlPage* page, xmlNodePtr node)
    : XmlElement((XmlPage*)page, node)
  {
  }

  HtmlElement::~HtmlElement()
  {
  }

  //============================= ACCESS     ===================================

  bool HtmlElement::isField()
  {
    if (getTagName() == "input") {
      string field_types[3] = { "text", "password", "file" };
      return isIncluded(getAttribute("type"), field_types, 3);
    } else if (getTagName() == "textarea") {
      return true;
    } else {
      return false;
    }
  }

  bool HtmlElement::isSelect()
  {
    return getTagName() == "select";
  }

  bool HtmlElement::isRadio()
  {
    return getTagName() == "input" && hasAttribute("type", "radio");
  }

  bool HtmlElement::isCheckBox()
  {
    return getTagName() == "input" && hasAttribute("type", "checkbox");
  }

  bool HtmlElement::isLink()
  {
    return getTagName() == "a";
  }

  bool HtmlElement::isButton()
  {
    if (getTagName() == "input") {
      string button_types[4] = { "button", "submit", "reset", "image" };
      return isIncluded(getAttribute("type"), button_types, 4);
    } else if (getTagName() == "button") {
      return true;
    } else {
      return false;
    }
  }

  //============================= OPERATIONS ===================================

  void HtmlElement::click()
  {
    bool can_continue = true;
    Browser* browser = page_->getEnclosingWindow()->getBrowser();

    if (browser->isJavaEnabled()) {
      // process javascripts and store result in can_continue
      // -> process parents clicks...
      // --> process document click
      // ---> process window click
    }
    
    if (can_continue) {
      if (isLink()) {
	Window* window;

	bool in_new_window = hasAttribute("target", "blank_");
	string url = page_->getUrlFor(getAttribute("href"));

	if (in_new_window)
	  window = page_->getEnclosingWindow()->getBrowser()->newWindow();
	else
	  window = page_->getEnclosingWindow();
	
	Request* request = Request::Get(url);
	request->enableCookieSession(browser->isCookieEnabled(), browser->getSessionToken());
	request->setReferer(page_->getUrl());

	Page* page = Page::Factory(request);
	window->setPage(page);
      }
    }
  }
}
