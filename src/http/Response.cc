#include "http/Response.h"
#include "utils/Helpers.h"

namespace mike {
  namespace http
  {
    /////////////////////////////// HELPERS //////////////////////////////////////

    string extractContentType(string mime)
    {
      if (mime.empty()) {
	return "text/plain";
      } else {
	int split = mime.find(";");
	return split > 0 ? mime.substr(0, split) : mime;
      }
    }

    list<string> extractCookies(string cookieString)
    {
      return list<string>();
    }

    /////////////////////////////// PUBLIC ///////////////////////////////////////

    //============================= LIFECYCLE ====================================

    Response::Response(long code, stringstream* content, map<string,string> headers, string content_type)
      : code_(code)
    {
      headers_ = headers;
      content_ = content;
      contentType_ = extractContentType(content_type);
    }

    Response::~Response()
    {
      headers_.clear();
      delete content_;
    }

    //============================= ACCESS     ===================================
    
    long Response::getCode()
    {
      return code_;
    }

    string Response::getBody()
    {
      return content_->str();
    }

    stringstream* Response::getStream()
    {
      return content_;
    }

    string Response::getHeader(string key)
    {
      map<string,string>::iterator header = headers_.find(key);
      return header != headers_.end() ? (*header).second : "";
    }

    string Response::getContentType()
    {
      return contentType_;
    }

    bool Response::isHtml()
    {
      string opts[2] = {"text/html", "application/xhtml+xml"};
      return isIncluded(getContentType(), opts, 2); 
    }

    bool Response::isXml()
    {
      string opts[2] = {"application/xml", "text/xml"};
      return isIncluded(getContentType(), opts, 2); 
    }
  }
}
