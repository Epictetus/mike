#include "mike/utils/http.h"

namespace mike {
  namespace http {
    namespace
    {
      size_t CurlWriter(char *data, size_t size, size_t nmemb, string *wdata)
      {
	if (wdata == NULL) return 0;
	wdata->append(data, size*nmemb);
	return size*nmemb;
      }
    }
    
    pRequest Request::GET(string url)
    {
      return new Request(url, "GET");
    }

    pRequest Request::POST(string url)
    {
      return new Request(url, "POST");
    }
    
    Request::Request(string url, string method)
      : url(url),
	method(method)
    {
      curl = curl_easy_init();
      curlHeaders = NULL;
      
      if (curl != NULL) {
	curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, curlErrorBuffer);
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
	curl_easy_setopt(curl, CURLOPT_AUTOREFERER, 1L); 
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWriter);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &curlBuffer);
	curl_easy_setopt(curl, CURLOPT_WRITEHEADER, &curlHeaderBuffer);
      }
    }

    Request::~Request()
    {
      curl_easy_cleanup(curl);
    }

    void Request::SetHeader(string header)
    {
      curlHeaders = curl_slist_append(curlHeaders, header.c_str());
    }

    void Request::SetData(string data)
    {
      curlPostData = data;
    }

    pResponse Request::Perform()
    {
      if (curl != NULL) {
	if (method == "POST") {
	  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, curlPostData.c_str());
	}

	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curlHeaders);

	if (curl_easy_perform(curl) == CURLE_OK) {
	  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &curlResponseCode);
	  return new Response(curlResponseCode, curlBuffer, curlHeaderBuffer);
	}
      }

      return NULL;
    }
    
    string Request::Url()
    {
      return url;
    }
    
    string Request::Method()
    {
      return method;
    }

    // Response...

    Response::Response(long code, string body, string headers)
      : code(code),
	body(body),
	headers(headers)
    {
    }

    Response::~Response()
    {
    }

    long Response::Code()
    {
      return code;
    }

    string Response::Body()
    {
      return body;
    }

    string Response::RawHeaders()
    {
      return headers;
    }
  }
}
