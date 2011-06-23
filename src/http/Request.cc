#include <algorithm>
#include "http/Request.h"

namespace mike {
  namespace http {
    namespace
    {
      size_t curlWriteHandler(void *ptr, size_t size, size_t nmemb, void *wdata)
      {
	if (wdata == NULL) {
	  return 0;
	}

	string buf = string((char*)ptr, size * nmemb);
	stringstream* response = (stringstream*)wdata;
	response->write(buf.c_str(), (streamsize)buf.size());

	return size * nmemb;
      }

      size_t curlHeaderHandler(void *ptr, size_t size, size_t nmemb, void *wdata)
      {
	if (wdata == NULL) {
	  return 0;
	}

	string line = string((char*)ptr);
	Headers* headers = (Headers*)wdata;
	headers->parseAndAppend(line);
	
	return size * nmemb;
      }
    }

    Request* Request::Get(string url)
    {
      return new Request(url, "GET");
    }

    Request* Request::Post(string url)
    {
      return new Request(url, "POST");
    }
    
    Request::Request(string url, string method)
      : url_(url)
      , method_(method)
    {
      curlHeaders_ = NULL;
      response_ = NULL;
    }

    Request::~Request()
    {
      curl_slist_free_all(curlHeaders_);
      cleanupResponse();
      cookies_.clear();
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

    void Request::setCookie(string cookie)
    {
      // TODO: hmm wandering, shall we add users possibility to set cookies from the client?
      throw "not implemented!";
    }

    string Request::getCookieFileName()
    {
      // TODO: make it configurable!
      return "/tmp/mike.cookies";
    }

    bool Request::perform()
    {
      bool result = false;
      cleanupResponse();
      
      if (prepareCurl()) {
	// Assign response headers container
	Headers response_headers;
	curl_easy_setopt(curl_, CURLOPT_WRITEHEADER, &response_headers);

	// Assign response body buffer
	stringstream* buffer = new stringstream();
	curl_easy_setopt(curl_, CURLOPT_WRITEDATA, (void*)buffer);

	if (curl_easy_perform(curl_) == CURLE_OK) {
	  // Extract response code
	  long response_code;
	  curl_easy_getinfo(curl_, CURLINFO_RESPONSE_CODE, &response_code);

	  // Extract content type
	  char* content_type;
	  curl_easy_getinfo(curl_, CURLINFO_CONTENT_TYPE, &content_type);

	  // Generate response
	  response_ = new Response(response_code, buffer, response_headers.toMap(), content_type);
	  result = true;
	}
      }

      cleanupCurl();
      return result;
    }

    void Request::cleanupResponse()
    {
      delete response_;
      response_ = NULL;
    }

    bool Request::prepareCurl()
    {
      curl_ = curl_easy_init();
      
      if (curl_ != NULL) {
	curl_easy_setopt(curl_, CURLOPT_URL, url_.c_str());
	curl_easy_setopt(curl_, CURLOPT_ERRORBUFFER, curlErrorBuffer_);
	curl_easy_setopt(curl_, CURLOPT_NOPROGRESS, 1L);

	// Auto redirecting and referer discovery
	curl_easy_setopt(curl_, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl_, CURLOPT_AUTOREFERER, 1L);

	// Skip SSL verifications
	curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(curl_, CURLOPT_SSL_VERIFYHOST, 0L);

	// Content and headers callbacks
	curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, curlWriteHandler);
	curl_easy_setopt(curl_, CURLOPT_HEADERFUNCTION, curlHeaderHandler);

	// Enable cookies
	curl_easy_setopt(curl_, CURLOPT_COOKIEJAR, getCookieFileName().c_str());
	curl_easy_setopt(curl_, CURLOPT_COOKIEFILE, getCookieFileName().c_str());

	// Set custom post data (if applicable)
	if (method_ == "POST") {
	  curl_easy_setopt(curl_, CURLOPT_POST, 1L);
	  curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, curlPostData_.c_str());
	}

	// Set custom headers
	curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, curlHeaders_);

	return true;
      }

      return false;
    }

    void Request::cleanupCurl()
    {
      curl_easy_cleanup(curl_);
    }
  }
}
