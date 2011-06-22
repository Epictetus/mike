#include "http/Response.h"
#include "utils/Helpers.h"

namespace mike {
  namespace http {
    namespace
    {
      string extractContentType(string mime)
      {
	if (mime.empty()) {
	  return "text/plain";
	} else {
	  int split = mime.find(";");
	  return split > 0 ? mime.substr(0, split) : mime;
	}
      }

      bool matchContentType(string mime, string opts[], int numopts)
      {
	for (int i = 0; i < numopts; i++) {
	  if (mime == opts[i]) {
	    return true;
	  }
	}

	return false;
      }
    }
    
    Response::Response(long code, stringstream* content, map<string,string> headers)
      : code_(code)
    {
      headers_  = headers;
      content_  = content;
    }

    Response::~Response()
    {
      headers_.clear();
      delete content_;
    }

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
      return extractContentType(getHeader("Content-Type"));
    }

    bool Response::isHtml()
    {
      string opts[2] = {"text/html", "application/xhtml+xml"};
      return matchContentType(getContentType(), opts, 2); 
    }

    bool Response::isXml()
    {
      string opts[2] = {"application/xml", "text/xml"};
      return matchContentType(getContentType(), opts, 2); 
    }
  }
}
