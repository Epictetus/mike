#include "xml/xml_element.h"

namespace mike
{
  XmlElement::XmlElement(xmlNode* node)
  {
    node_ = node;
  }

  XmlElement::~XmlElement()
  {
    // XXX: find out if we need to delete node_ here... 
  }
}
