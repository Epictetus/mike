#include <string>
#include <algorithm>
#include "mike/utils/http.h"
#include "mike/utils/string.h"

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

      size_t CurlHeaderHandler(void *ptr, size_t size, size_t nmemb, void *wdata)
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
	curl_easy_setopt(curl, CURLOPT_WRITEHEADER, (void*)&curlResponseHeaders);
	curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, &CurlHeaderHandler);
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
	  return new Response(curlResponseCode, curlBuffer, curlResponseHeaders);
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

    Response::Response(long code, string body, HttpHeaderMap header)
      : code(code),
	body(body),
	headers(header)
    {
    }

    Response::~Response()
    {
      headers.clear();
    }

    long Response::Code()
    {
      return code;
    }

    string Response::Body()
    {
      return body;
    }

    string Response::GetHeader(string key)
    {
      HttpHeaderMap::iterator header = headers.find(key);
      return header != headers.end() ? (*header).second : "";
    }

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

    string Response::ContentType()
    {
      string type = GetHeader("Content-Type");

      if (type == "") {
	"text/html";
      } else {
	int split = type.find(";");
	return split > 0 ? type.substr(0, split) : type;
      }
    }
  }
}
