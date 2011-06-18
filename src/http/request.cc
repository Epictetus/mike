#include <algorithm>
#include "http/request.h"

namespace mike {
  namespace http {
    namespace
    {
      size_t curlWriteHandler(char *data, size_t size, size_t nmemb, string *wdata)
      {
	if (wdata == NULL) {
	  return 0;
	}
      
	wdata->append(data, size*nmemb);
	return size*nmemb;
      }

      size_t curlHeaderHandler(void *ptr, size_t size, size_t nmemb, void *wdata)
      {
	if (wdata == NULL) {
	  return 0;
	}

	string line = string((char*)ptr);
	Headers* headers = (Headers*)wdata;
	headers->parseAndAppend(line);
	
	return size*nmemb;
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
	curl_easy_setopt(curl_, CURLOPT_WRITEHEADER, (void*)&responseHeaders_);
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
	  response_ = new Response(curlResponseCode_, curlBuffer_, responseHeaders_.toMap());
	  return true;
	}
      }
    
      return false;
    }

    void Request::cleanupResponse()
    {
      responseHeaders_.clear();

      if (response_ != NULL) {
	delete response_;
	response_ = NULL;
      }
    }
  }
}
