#include <string.h>
#include "xml/XmlPage.h"

namespace mike {
  namespace
  {
    void xmlErrorHandler(void *ctx, const char *msg, ...)
    {
      // so far nothing, just mute errors...
    }

    void getElementsByTagNameIter(XmlPage* page, string tag, xmlNodePtr node, vector<XmlElement*>* elems)
    {
      while (node) {
	if (node->name && (strcmp((char*)node->name, tag.c_str()) == 0)) {
	  elems->push_back(new XmlElement(page, node));
	}
	
	getElementsByTagNameIter(page, tag, node->children, elems);
	node = node->next;
      }
    }
  }
  
  XmlPage::XmlPage(Request* request)
    : RegularPage(request)
  {
    doc_ = NULL;
    type_ = XML_PAGE;
    prepareDocument();
  }

  XmlPage::~XmlPage()
  {
    cleanupDocument();
  }

  vector<XmlElement*> XmlPage::getElementsByXpath(string xpath)
  {
    vector<XmlElement*> result;

    if (doc_) {
      // Setup XPath stuff and evaluate expression
      xmlChar* cxpath = xmlCharStrdup(xpath.c_str());
      xmlXPathContextPtr ctx = xmlXPathNewContext(doc_);
      xmlXPathObjectPtr found = xmlXPathEvalExpression(cxpath, ctx);

      // Assign found elements (if any) to results vector.
      if (found && !xmlXPathNodeSetIsEmpty(found->nodesetval)) {
	xmlNodeSetPtr nodeset = found->nodesetval;
	XmlElement* elements[nodeset->nodeNr];
	
	for (int i = 0; i < nodeset->nodeNr; i++) {
	  elements[i] = new XmlElement(this, nodeset->nodeTab[i]);
	}

	result.assign(elements, elements + nodeset->nodeNr);
      }
      
      // Free XPath stuff.
      xmlXPathFreeContext(ctx);
      xmlXPathFreeObject(found);
      xmlFree(cxpath);
    }
    
    return result;
  }

  vector<XmlElement*> XmlPage::getElementsByTagName(string tag)
  {
    vector<XmlElement*> elems;
      
    if (doc_ && !tag.empty()) {
      getElementsByTagNameIter(this, tag, doc_->children, &elems);
    }

    return elems;
  }

  void XmlPage::reload()
  {
    Page::reload();
    prepareDocument();
  }

  void XmlPage::prepareDocument()
  {
    if (isLoaded()) {
      cleanupDocument();
      parseDocument();
    }
  }

  void XmlPage::parseDocument()
  {
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
