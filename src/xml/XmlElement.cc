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
    for (map<string,xmlChar*>::iterator it = attrsCache_.begin(); it != attrsCache_.end(); it++) {
      xmlFree((*it).second);
    }

    attrsCache_.clear();
    
    // XXX: find out if we need to delete node_ here... 
  }

  string XmlElement::getAttribute(string name)
  {
    xmlChar* attr_name = xmlCharStrdup(name.c_str());
    xmlChar* value = NULL;

    map<string,xmlChar*>::iterator found = attrsCache_.find(name);

    if (found != attrsCache_.end()) {
      value = (*found).second;
    } else {
      if ((value = xmlGetProp(node_, attr_name)) != NULL) {
	attrsCache_[name] = value;
      } else {
	return "";
      }
    }
    
    return string((char*)value, xmlStrlen(value));
  }

  string XmlElement::getText()
  {
    
  }

  string XmlElement::getContent()
  {
    
  }
}
