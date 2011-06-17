#include <string>
#include <algorithm>
#include "mike/utils/http.h"
#include "mike/utils/string.h"

namespace mike {
  namespace http {
    namespace
    {      
      size_t curlWriteHandler(char *data, size_t size, size_t nmemb, string *wdata)
      {
	if (wdata == NULL) return 0;
	wdata->append(data, size*nmemb);
	return size*nmemb;
      }

      size_t curlHeaderHandler(void *ptr, size_t size, size_t nmemb, void *wdata)
      {
	if (wdata == NULL) return 0;
	string header = string((char*)ptr);
	int split = header.find(':');

	if (split >= 0) {
	  string key = rtrim(rtrim(trim((char*)header.substr(0, split).c_str()),'\n'),'\r');
	  string value = rtrim(rtrim(trim((char*)header.substr(split+1).c_str()),'\n'),'\r');
	  HttpHeaderMap *headers = (HttpHeaderMap*)wdata;
	  (*headers)[key] = value;
	}
	
	return size*nmemb;
      }
    }
    
    Request* Request::GET(string url)
    {
      return new Request(url, "GET");
    }

    Request* Request::POST(string url)
    {
      return new Request(url, "POST");
    }
    
    Request::Request(string url, string method)
      : url_(url)
      , method_(method)
    {
      curl_ = curl_easy_init();
      curlHeaders_ = NULL;

      if (curl_ != NULL) {
	curl_easy_setopt(curl_, CURLOPT_ERRORBUFFER, curlErrorBuffer_);
	curl_easy_setopt(curl_, CURLOPT_URL, url_.c_str());
	curl_easy_setopt(curl_, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl_, CURLOPT_NOPROGRESS, 1L);
	curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYHOST, 0L);
	curl_easy_setopt(curl_, CURLOPT_AUTOREFERER, 1L); 
	curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, curlWriteHandler);
	curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &curlBuffer_);
	curl_easy_setopt(curl_, CURLOPT_WRITEHEADER, (void*)&curlResponseHeaders_);
	curl_easy_setopt(curl_, CURLOPT_HEADERFUNCTION, &curlHeaderHandler);
      }

      response_ = NULL;
    }

    Request::~Request()
    {
      curl_easy_cleanup(curl_);
      cleanupResponse();
    }

    Response* Request::getResponse()
    {
      return response_;
    }
    
    string Request::getUrl()
    {
      return url_;
    }
    
    string Request::getMethod()
    {
      return method_;
    }

    bool Request::isReady()
    {
      return response_ != NULL;
    }
    
    void Request::setHeader(string header)
    {
      curlHeaders_ = curl_slist_append(curlHeaders_, header.c_str());
    }

    void Request::setData(string data)
    {
      curlPostData_ = data;
    }

    bool Request::perform()
    {
      cleanupResponse();
      
      if (curl_ != NULL) {
	if (method_ == "POST") {
	  curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, curlPostData_.c_str());
	}

	curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, curlHeaders_);

	if (curl_easy_perform(curl_) == CURLE_OK) {
	  curl_easy_getinfo(curl_, CURLINFO_RESPONSE_CODE, &curlResponseCode_);
	  response_ = new Response(curlResponseCode_, curlBuffer_, curlResponseHeaders_);
	  return true;
	}
      }

      return false;
    }

    void Request::cleanupResponse()
    {
      if (response_ != NULL) {
	delete response_;
	response_ = NULL;
      }
    }

    // Response...

    Response::Response(long code, string body, HttpHeaderMap header)
      : code_(code)
      , body_(body)
      , headers_(header)
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
      HttpHeaderMap::iterator header = headers_.find(key);
      return header != headers_.end() ? (*header).second : "";
    }

    /*
    bool Response::IsHTML()
    {
      return ContentType() == "text/html" ||
             ContentType() == "application/xhtml+xml";
    }

    bool Response::IsXML()
    {
      return ContentType() == "application/xml" ||
             ContentType() == "text/xml";
    }
    */
    
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
  }
}
