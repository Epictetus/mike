#include "http/response.h"

namespace mike {
  namespace http
  {
    Response::Response(long code, string body, map<string,string> headers)
      : code_(code)
      , body_(body)
      , headers_(headers)
    {
    }

    Response::~Response()
    {
      headers_.clear();
    }

    long Response::getCode()
    {
      return code_;
    }

    string Response::getBody()
    {
      return body_;
    }

    string Response::getHeader(string key)
    {
      map<string,string>::iterator header = headers_.find(key);
      return header != headers_.end() ? (*header).second : "";
    }

    string Response::getContentType()
    {
      string type = getHeader("Content-Type");

      if (type == "") {
	"text/html";
      } else {
	int split = type.find(";");
	return split > 0 ? type.substr(0, split) : type;
      }
    }

    bool Response::isHtml()
    {
      bool result;
      result = result || (getContentType() == "text/html");
      result = result || (getContentType() == "application/xhtml+xml");
      return result;
    }

    bool Response::isXml()
    {
      bool result;
      result = result || (getContentType() == "application/xml");
      result = result || (getContentType() == "text/xml");
      return result;
    }
  }
}
