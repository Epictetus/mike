#include "page.h"
#include "xml/xml_page.h"
#include "html/html_page.h"

namespace mike
{
  Page* Page::Build(Request* request)
  {
    if (request && request->perform()) {
      Response* response = request->getResponse();

      if (response->isHtml()) {
	return new HtmlPage(request);
      } else if (response->isXml()) {
	return new XmlPage(request);
      } else if (response->isText()) {
	//return new TextPage(request);
      } else {
	// return new BinaryPage(request);
      }
    }
    
    return NULL;
  }

  Page::Page(Request* request, PageType type)
    : type_(type)
  {
    request_ = request;
  }

  Page::~Page()
  {
    delete request_;
  }

  Request* Page::getRequest()
  {
    return request_;
  }

  Response* Page::getResponse()
  {
    return request_->getResponse();
  }

  string Page::getUrl()
  {
    return request_->getUrl();
  }

  bool Page::isText()
  {
    return type_ == TEXT_PAGE;
  }

  bool Page::isXml()
  {
    return (type_ == XML_PAGE || type_ == HTML_PAGE);
  }

  bool Page::isHtml()
  {
    return type_ == HTML_PAGE;
  }

  bool Page::isBinary()
  {
    return type_ == BINARY_PAGE;
  }

  XmlPage* Page::toXmlPage()
  {
    return isXml() ? (XmlPage*)this : NULL;
  }

  HtmlPage* Page::toHtmlPage()
  {
    return isHtml() ? (HtmlPage*)this : NULL;
  }

  bool Page::isLoaded()
  {
    return (request_ && request_->isReady());
  }
  
  void Page::reload()
  {
    if (request_ != NULL) {
      request_->perform();
    }
  }
}
