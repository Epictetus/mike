#include "html/HtmlElement.h"
#include "html/HtmlPage.h"

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

  /////////////////////////////// PROTECTED ////////////////////////////////////

  void HtmlElement::unlink()
  {
    if (node_) {
      xmlUnlinkNode(node_);
      xmlFreeNode(node_);
      node_ = NULL;
    }
  }
}
