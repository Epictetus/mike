#ifndef _MIKE_UTILS_HTTP_H_
#define _MIKE_UTILS_HTTP_H_

#include <string>
#include <map>
#include <curl/curl.h>

using namespace std;

namespace mike
{
  namespace http
  {
    class Request;
    class Response;
    
    typedef Request* pRequest;
    typedef Response* pResponse;
    typedef struct curl_slist* CURLheaders;
    typedef map<string,string> HttpHeaderMap;
    
    class Request
    {
    private:
      string url;
      string method;
      CURL *curl;
      CURLheaders curlHeaders;
      string curlPostData;
      string curlBuffer;
      string curlHeaderBuffer;
      long curlResponseCode;
      HttpHeaderMap curlResponseHeaders;
      char curlErrorBuffer[CURL_ERROR_SIZE];
    public:
      static pRequest GET(string url);
      static pRequest POST(string url);
      Request(string url, string method);
      virtual ~Request();
      void SetHeader(string header);
      void SetData(string data);
      string Url();
      string Method();
      pResponse Perform();
    };

    class Response
    {
    private:
      long code;
      string body;
      string rawHeaders;
      HttpHeaderMap headers;
    public:
      Response(long code, string body, HttpHeaderMap headers);
      virtual ~Response();
      long Code();
      string Body();
      string GetHeader(string key);
      bool IsHTML();
      bool IsXML();
      string ContentType();
    };
  }
}

#endif /* _MIKE_UTILS_HTTP_H_ */
