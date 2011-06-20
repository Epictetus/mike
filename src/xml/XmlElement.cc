#include "xml/XmlElement.h"
#include "xml/XmlPage.h"

namespace mike
{
  XmlElement::XmlElement(XmlPage* page, xmlNode* node)
  {
    page_ = page;
    node_ = node;
  }

  XmlElement::~XmlElement()
  {
    // XXX: find out if we need to delete node_ here... 
  }
}
