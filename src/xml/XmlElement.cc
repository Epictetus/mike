#include "xml/XmlElement.h"
#include "xml/XmlPage.h"
#include "utils/Helpers.h"

namespace mike
{
  /////////////////////////////// PUBLIC ///////////////////////////////////////

  //============================= LIFECYCLE ====================================

  XmlElement::XmlElement(XmlPage* page, xmlNodePtr node)
  {
    page_ = page;
    node_ = node;
  }

  XmlElement::~XmlElement()
  {
  }

  //============================= ACCESS     ===================================
  
  string XmlElement::getAttribute(string name)
  {
    xmlChar* attr_name = xmlCharStrdup(name.c_str());
    xmlChar* value = NULL;
    string result = "";
    
    if (node_ && (value = xmlGetProp(node_, attr_name)) != NULL) {
      result = (char*)value;
      xmlFree(attr_name);
      xmlFree(value);
    }

    return result;
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
    xmlChar* content = xmlNodeGetContent(node_);
    string result = (char*)content;
    xmlFree(content);
    return content ? result : "";
  }

  string XmlElement::getText()
  {
    return getContent();
  }

  bool XmlElement::hasContent()
  {
    return !(string(strstrip(getContent())).empty());
  }

  bool XmlElement::hasContent(string value)
  {
    return (value == getContent());
  }

  bool XmlElement::hasText()
  {
    return hasContent();
  }

  bool XmlElement::hasText(string value)
  {
    return hasContent(value);
  }

  string XmlElement::getName()
  {
    return (char*)node_->name;
  }

  string XmlElement::getTagName()
  {
    return getName();
  }

  bool XmlElement::hasChildren()
  {
    return (node_ && node_->children);
  }

  string XmlElement::getPath()
  {
    xmlChar* path = xmlGetNodePath(node_);
    string result = (char*)path;
    xmlFree(path);
    return result;
  }

  // XXX: HtmlElement should use htmlNodeDump func.
  string XmlElement::toXml()
  {
    xmlBufferPtr buffer = xmlBufferCreate();
    xmlNodeDump(buffer, node_->doc, node_, 0, 0);
    string xml = (char*)buffer->content;
    xmlBufferFree(buffer);
    return xml;
  }

  string XmlElement::dump()
  {
    return toXml();
  }
}
