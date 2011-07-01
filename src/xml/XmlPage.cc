#include <string.h>
#include "xml/XmlPage.h"

namespace mike
{
  /////////////////////////////// HELPERS //////////////////////////////////////

  void xmlErrorHandler(void *ctx, const char *msg, ...)
  {
    // so far nothing, just mute errors...
  }

  void getElementsByTagNameIter(XmlPage* page, string tag, xmlNodePtr node, XmlElementSet* elems)
  {
    while (node) {
      if (node->name && (strcmp((char*)node->name, tag.c_str()) == 0)) {
	elems->push_back(new XmlElement(page, node));
      }
	
      getElementsByTagNameIter(page, tag, node->children, elems);
      node = node->next;
    }
  }

  xmlXPathObjectPtr findByXPath(xmlDocPtr doc, string xpath)
  {
    if (doc) {
      // Setup XPath stuff and evaluate expression
      xmlChar* cxpath = xmlCharStrdup(xpath.c_str());
      xmlXPathContextPtr ctx = xmlXPathNewContext(doc);
      xmlXPathObjectPtr found = xmlXPathEvalExpression(cxpath, ctx);

      // Free XPath stuff
      xmlXPathFreeContext(ctx);
      xmlFree(cxpath);

      // Return results if any
      if (found == NULL) {
	throw InvalidXpathExpressionError(xpath);
      } else if (!xmlXPathNodeSetIsEmpty(found->nodesetval)) {
	return found;
      } else {
	xmlXPathFreeObject(found);
      }
    }
      
    return NULL;
  }

  /////////////////////////////// PUBLIC ///////////////////////////////////////
  
  //============================= LIFECYCLE ====================================
  
  XmlPage::XmlPage(Request* request)
    : Page(request, XML_PAGE)
  {
    doc_ = NULL;
    prepareDocument();
  }

  XmlPage::~XmlPage()
  {
    cleanupDocument();
  }

  //============================= ACCESS     ===================================
  
  XmlElementSet* XmlPage::getElementsByXpath(string xpath)
  {
    XmlElementSet* result = new XmlElementSet();
    xmlXPathObjectPtr found = findByXPath(doc_, xpath);

    if (found) {
      xmlNodeSetPtr nodeset = found->nodesetval;
      XmlElement* elements[nodeset->nodeNr];
	
      for (int i = 0; i < nodeset->nodeNr; i++) {
	elements[i] = new XmlElement(this, nodeset->nodeTab[i]);
      }
      
      result = new XmlElementSet(elements, nodeset->nodeNr);
      xmlXPathFreeObject(found);
    }
      
    return result;
  }
  
  XmlElement* XmlPage::getElementByXpath(string xpath)
  {
    xmlXPathObjectPtr found = findByXPath(doc_, xpath);
    XmlElement* result = NULL;
    
    if (found) {
      result = new XmlElement(this, found->nodesetval->nodeTab[0]);
      xmlXPathFreeObject(found);
    } else {
      throw ElementNotFoundError("XPath = " + xpath);
    }
    
    return result;
  }

  XmlElementSet* XmlPage::getElementsByTagName(string tag)
  {
    XmlElementSet* elems = new XmlElementSet();
      
    if (doc_ && !tag.empty()) {
      getElementsByTagNameIter(this, tag, doc_->children, elems);
    }

    return elems;
  }

  //============================= OPERATIONS ===================================
  
  void XmlPage::reload()
  {
    Page::reload();
    prepareDocument();
  }

  /////////////////////////////// PROTECTED  ///////////////////////////////////
  
  void XmlPage::prepareDocument()
  {
    cleanupDocument();
    parseDocument();
  }

  void XmlPage::parseDocument()
  {
    xmlSetGenericErrorFunc((void*)this, xmlErrorHandler);
    xmlChar* body = xmlCharStrdup(getResponse()->getBody().c_str());
    doc_ = xmlReadDoc(body, getUrl().c_str(), "utf-8", XML_PARSE_RECOVER | XML_PARSE_NOERROR | XML_PARSE_NOWARNING);
    xmlFree(body);
  }
  
  void XmlPage::cleanupDocument()
  {
    if (doc_ != NULL) {
      xmlFreeDoc(doc_);
      doc_ = NULL;
    }
  }
}
