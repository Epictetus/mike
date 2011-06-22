#include "Page.h"
#include "RegularPage.h"
#include "xml/XmlPage.h"
#include "html/HtmlPage.h"

namespace mike
{
  Page* Page::Build(Request* request)
  {
    if (request && request->perform()) {
      Response* response;

      if ((response = request->getResponse()) != NULL) {
	if (response->isHtml()) {
	  return new HtmlPage(request);
	} else if (response->isXml()) {
	  return new XmlPage(request);
	} else {
	  return new RegularPage(request);
	}
      }
    }

    return new Page(request, UNKNOWN_PAGE);
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

  bool Page::isXml()
  {
    return (type_ == XML_PAGE || type_ == HTML_PAGE);
  }

  bool Page::isHtml()
  {
    return type_ == HTML_PAGE;
  }

  bool Page::isRegular()
  {
    return type_ == REGULAR_PAGE;
  }

  XmlPage* Page::toXmlPage()
  {
    return isXml() ? (XmlPage*)this : NULL;
  }

  HtmlPage* Page::toHtmlPage()
  {
    return isHtml() ? (HtmlPage*)this : NULL;
  }

  RegularPage* Page::toRegularPage()
  {
    return isRegular() ? (RegularPage*)this : NULL;
  }

  bool Page::isLoaded()
  {
    return (type_ != UNKNOWN_PAGE && request_ && request_->isReady());
  }
  
  void Page::reload()
  {
    if (request_ != NULL) {
      request_->perform();
    }
  }
}
