#include "utils/Helpers.h"
#include "html/HtmlElement.h"
#include "html/HtmlPage.h"
#include "Window.h"
#include "Frame.h"
#include "Browser.h"

#include "html/HtmlAnchorElement.h";

namespace mike
{  
  /////////////////////////////// PUBLIC ///////////////////////////////////////

  //============================= LIFECYCLE ====================================

  HtmlElement* HtmlElement::Factory(HtmlPage* page, xmlNodePtr node)
  {
    if (node) {
      string tag = (char*)node->name;

      if (tag == "a")
	return (HtmlElement*)(new HtmlAnchorElement(page, node));
      else
	return new HtmlElement(page, node);
    }

    throw "Invalid HTML node.";
  }
  
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

  bool HtmlElement::click()
  {
    if (getBrowser()->isJavaEnabled()) {
      // process javascripts and store result in can_continue
      // -> process parents clicks...
      // --> process document click
      // ---> process window click
    }

    return true;
  }

  /////////////////////////////// PROTECTED ////////////////////////////////////
  
  Browser* HtmlElement::getBrowser()
  {
    return page_->getEnclosingWindow()->getBrowser();
  }
}
