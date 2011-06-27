#include "xml/XmlElement.h"
#include "xml/XmlPage.h"
#include "utils/Helpers.h"

namespace mike
{
  XmlElement::XmlElement(XmlPage* page, xmlNodePtr node)
  {
    printf("\n---> XmlElement created!");

    page_ = page;
    node_ = node;
  }

  XmlElement::~XmlElement()
  {
    printf("\n---> XmlElement destroyed");
      
    for (map<string,xmlChar*>::iterator it = attrsCache_.begin(); it != attrsCache_.end(); it++)
      xmlFree((*it).second);
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

  bool XmlElement::hasAttribute(string name, string value)
  {
    return hasAttribute(name) ? (value == getAttribute(name)) : false;
  }
  
  string XmlElement::getContent()
  {
    return hasChildren() ? (char*)node_->children->content : "";
  }

  bool XmlElement::hasContent()
  {
    return !(string(strstrip(getContent())).empty());
  }

  bool XmlElement::hasContent(string value)
  {
    return (value == getContent());
  }

  string XmlElement::getName()
  {
    return (char*)node_->name;
  }

  bool XmlElement::hasChildren()
  {
    return (node_ && node_->children);
  }
}
