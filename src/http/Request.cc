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
      curl_ = curl_easy_init();
      curlHeaders_ = NULL;
      response_ = NULL;
      
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
      }
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
	// Set custom post data (if applicable)
	if (method_ == "POST") {
	  curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, curlPostData_.c_str());
	}

	// Set custom headers
	curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, curlHeaders_);

	// Assign response headers container
	Headers headers;
	curl_easy_setopt(curl_, CURLOPT_WRITEHEADER, &headers);

	// Assign response body buffer
	stringstream* buffer = new stringstream();
	curl_easy_setopt(curl_, CURLOPT_WRITEDATA, (void*)buffer);

	if (curl_easy_perform(curl_) == CURLE_OK) {
	  // Extract response code
	  long response_code;
	  curl_easy_getinfo(curl_, CURLINFO_RESPONSE_CODE, &response_code);

	  // Generate response
	  response_ = new Response(response_code, buffer, headers.toMap());

	  return true;
	}
      }
    
      return false;
    }

    void Request::cleanupResponse()
    {
      delete response_;
      response_ = NULL;
    }
  }
}
