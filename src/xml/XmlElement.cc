#include "xml/XmlElement.h"
#include "xml/XmlPage.h"

namespace mike
{
  XmlElement::XmlElement(XmlPage* page, xmlNodePtr node)
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
  }

  string XmlElement::getAttribute(string name)
  {
    xmlChar* attr_name = xmlCharStrdup(name.c_str());
    xmlChar* value = NULL;

    map<string,xmlChar*>::iterator found = attrsCache_.find(name);

    if (found != attrsCache_.end()) {
      value = (*found).second;
    } else {
      if (node_ && (value = xmlGetProp(node_, attr_name)) != NULL) {
	xmlFree(attr_name);
	attrsCache_[name] = value;
      } else {
	return "";
      }
    }
    
    return string((char*)value, xmlStrlen(value));
  }

  bool XmlElement::hasAttribute(string name)
  {
    xmlChar* attr_name = xmlCharStrdup(name.c_str());
    bool result = xmlHasProp(node_, attr_name);
    xmlFree(attr_name);
    return result;
  }
  
  string XmlElement::getContent()
  {
    return node_ ? (char*)node_->children->content : "";
  }
}
