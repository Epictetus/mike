#include "xml/xml_page.h"

namespace mike {
  namespace
  {
    void xmlErrorHandler(void *ctx, const char *msg, ...)
    {
      // so far nothing, just mute errors...
    }
  }
  
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

  vector<XmlElement*> XmlPage::getElementsByXpath(string xpath)
  {
    vector<XmlElement*> result;

    // Setup XPath stuff and evaluate expression
    xmlChar* cxpath = xmlCharStrdup(xpath.c_str());
    xmlXPathContextPtr ctx = xmlXPathNewContext(doc_);
    xmlXPathObjectPtr found = xmlXPathEvalExpression(cxpath, ctx);

    // Assign found elements (if any) to results vector.
    if (found && !xmlXPathNodeSetIsEmpty(found->nodesetval)) {
      xmlNodeSetPtr nodeset = found->nodesetval;
      XmlElement* elements[nodeset->nodeNr];

      for (int i = 0; i < nodeset->nodeNr; i++) {
	elements[i] = new XmlElement(nodeset->nodeTab[i]);
      }

      result.assign(elements, elements + nodeset->nodeNr);
    }

    // Free XPath stuff. 
    xmlXPathFreeContext(ctx);
    xmlXPathFreeObject(found);

    return result;
  }

  vector<XmlElement*> XmlPage::getElementsByTagName(string tag)
  {
    
  }

  void XmlPage::prepareDocument()
  {
    cleanupDocument();
    registerErrorHandler();

    if (request_->isReady()) {
      xmlChar* body = xmlCharStrdup(getResponse()->getBody().c_str());
      doc_ = xmlParseDoc(body);
    }
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
