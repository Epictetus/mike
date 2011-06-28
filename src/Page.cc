#include "Page.h"
#include "Frame.h"
#include "Window.h"
#include "RegularPage.h"
#include "xml/XmlPage.h"
#include "html/HtmlPage.h"

namespace mike
{
  Page* Page::Open(string url)
  {
    http::Request* req = http::Request::Get(url);
    return Build(req);
  }
  
  Page* Page::Build(Request* request)
  {
    if (request && request->perform()) {
      Response* response = request->getResponse();
      
      if (response) {
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
    frame_ = NULL;
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

  Frame* Page::getEnclosingFrame()
  {
    return frame_;
  }

  Window* Page::getEnclosingWindow()
  {
    return frame_ ? frame_->getWindow() : NULL;
  }

  string Page::getUrl()
  {
    return request_->getUrl();
  }

  stringstream* Page::getStream()
  {
    return getResponse()->getStream();
  }

  string Page::getContent()
  {
    return getResponse()->getBody();
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
    if (request_) {
      request_->perform();
    }
  }

  void Page::openInFrame(Frame* frame)
  {
    frame_ = frame;
    frame_->cleanup();
    frame_->getHistory()->push(this);
  }
}
