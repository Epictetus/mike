#include "Page.h"
#include "Frame.h"
#include "Window.h"
#include "xml/XmlPage.h"
#include "html/HtmlPage.h"

namespace mike
{
  /////////////////////////////// PUBLIC ///////////////////////////////////////

  //============================= LIFECYCLE ====================================

  Page* Page::Open(string url)
  {
    Request* req = Request::Get(url);
    return Factory(req);
  }
  
  Page* Page::Factory(Request* request)
  {
    if (request) {
      Response* response = request->perform();
      
      if (response) {
	if (response->isHtml()) {
	  return new HtmlPage(request);
	} else if (response->isXml()) {
	  return new XmlPage(request);
	} else {
	  return new Page(request);
	}
      }
    }

    throw "Invalid request.";
  }

  Page::Page(Request* request, PageType type/*=UNKNOWN_PAGE*/)
    : type_(type)
  {
    request_ = request;
    frame_ = NULL;
  }

  Page::~Page()
  {
    delete request_;
  }

  //============================= ACCESS     ===================================
  
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

  Frame* Page::getEnclosingFrame()
  {
    return frame_;
  }

  Window* Page::getEnclosingWindow()
  {
    return frame_ ? frame_->getWindow() : NULL;
  }

  //============================= OPERATIONS ===================================
  
  void Page::reload()
  {
    request_->perform();
  }

  void Page::enclose(Frame* frame)
  {
    if (frame_ == NULL) {
      frame_ = frame;
      frame_->setPage(this);
    }
  }
}
