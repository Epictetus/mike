#ifndef _MIKE_UTILS_HTTP_H_
#define _MIKE_UTILS_HTTP_H_

#include <string>
#include <map>
#include <curl/curl.h>

using namespace std;

namespace mike {
  namespace http
  {
    class Request;
    class Response;
    
    typedef CURL Curl;
    typedef struct curl_slist* CurlHeaders;
    typedef map<string,string> HttpHeaderMap;
      
    class Request
    {
    public:
      static Request* GET(string url);
      static Request* POST(string url);
      Request(string url, string method);
      virtual ~Request();
      void setHeader(string header);
      void setData(string data);
      string getUrl();
      string getMethod();
      Response* getResponse();
      bool perform();
      bool isReady();
    protected:
      string url_;
      string method_;
      Response* response_;
      Curl* curl_;
      CurlHeaders curlHeaders_;
      HttpHeaderMap curlResponseHeaders_;
      string curlPostData_;
      string curlBuffer_;
      string curlHeaderBuffer_;
      long curlResponseCode_;
      char curlErrorBuffer_[CURL_ERROR_SIZE];
      void cleanupResponse();
    };

    class Response
    {
    public:
      Response(long code, string body, HttpHeaderMap headers);
      virtual ~Response();
      long getCode();
      string getBody();
      string getHeader(string key);
      string getContentType();
    protected:
      long code_;
      string body_;
      HttpHeaderMap headers_;
    };
  }
}

#endif /* _MIKE_UTILS_HTTP_H_ */
