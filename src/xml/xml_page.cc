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

  XmlElementSet* XmlPage::getElementsByXpath(string xpath)
  {
    
  }

  XmlElementSet* XmlPage::getElementsByTagName(string tag)
  {

  }

  void XmlPage::prepareDocument()
  {
    cleanupDocument();
    xmlSetGenericErrorFunc((void*)this, xmlErrorHandler);

    if (request_->isReady()) {
      xmlChar *body = xmlCharStrdup(getResponse()->getBody().c_str());

      if (isHtml()) {
	doc_ = htmlParseDoc(body, NULL);
      } else if (isXml()) {
	doc_ = xmlParseDoc(body);
      }
    }
  }

  void XmlPage::cleanupDocument()
  {
    if (doc_ != NULL) {
      xmlFreeDoc(doc_);
      doc_ = NULL;
    }
  }
}
