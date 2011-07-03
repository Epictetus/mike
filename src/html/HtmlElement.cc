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
}
