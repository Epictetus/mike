#include "xml/XmlPage.h"

namespace mike {
  namespace
  {
    void xmlErrorHandler(void *ctx, const char *msg, ...)
    {
      // so far nothing, just mute errors...
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
    // TODO: do it without using xpath you lazy bastard!!
    return getElementsByXpath("//" + tag);
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
      registerErrorHandler();
      parseDocument();
    }
  }

  void XmlPage::parseDocument()
  {
    xmlChar* body = xmlCharStrdup(getResponse()->getBody().c_str());
    doc_ = xmlParseDoc(body);
    xmlFree(body);
  }
  
  void XmlPage::cleanupDocument()
  {
    if (doc_ != NULL) {
      xmlFreeDoc(doc_);
      doc_ = NULL;
    }
  }

  void XmlPage::registerErrorHandler()
  {
    xmlSetGenericErrorFunc((void*)this, xmlErrorHandler);
  }
}
