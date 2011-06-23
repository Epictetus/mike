#ifndef _MIKE_HTTP_REQUEST_H_
#define _MIKE_HTTP_REQUEST_H_

#include <map>
#include <list>
#include <string>
#include <sstream>
#include <curl/curl.h>
#include "http/Response.h"
#include "http/Headers.h"
#include "http/Cookie.h"

namespace mike {
  namespace http
  {
    using namespace std;

    typedef CURL Curl;
    typedef struct curl_slist* CurlList;

    /**
     * HTTP request class built at top of CURL library. This class rather will
     * not be used directly in code, it's base for browser specific requests.
     *
     * Example:
     *
     * <code>
     *   mike::http::Request* req = mike::http::Request::Get("http://www.mypage.com");
     *   req->setHeader("Custom-Header: Forfiter");
     *   assert(req->pefrorm());
     *   string content = req->getResponse()->getBody();
     * </code>
     *
     */
    class Request
    {
    public:
      /**
       * Creates new GET request for given url.
       *
       */
      static Request* Get(string url);

      /**
       * Creates new POST request for given url.
       *
       */
      static Request* Post(string url);

      /**
       * Constructor.
       *
       */
      Request(string url, string method);

      /**
       * Destructor.
       *
       */
      ~Request();

      /**
       * This method allows you to set custom HTTP headers for this request, eg:
       *
       * <code>
       *   req->setHeader("Referer: http://www.referersite.com");
       * </code>
       *
       */
      void setHeader(string header);

      /**
       * Sets given string as POST data, eg:
       *
       * <code>
       *   req->setData("user=forfiter&password=szwagier");
       * </code>
       *
       */
      void setData(string data);

      /**
       * Appends given cookie string to this request headers.
       *
       * <code>
       *   req->setCookie("foo=bar");
       *   req->perform();
       * </code>
       *  
       */
      void setCookie(string cookie);

      /**
       * Returns URL for which current request has been created.
       *
       */
      string getUrl();

      /**
       * Returns request method defined by constructor.
       *
       */
      string getMethod();

      /**
       * Returns HTTP response generated after performing this request. If request
       * has not been performed yet then obviously <code>NULL</code> will be returned.
       *
       * Check the <code>http/request.h</code> file to get more details.
       *
       */
      Response* getResponse();

      /**
       * Performs current request. Returns <code>true</code> when everything went fine.
       *
       */
      bool perform();

      /**
       * Returns <code>true</code> if request has been performed and response has been
       * generated properly. 
       *
       */
      bool isReady();

      /**
       * Returns name of file where cookies should be stored.
       *
       *
       */
      string getCookieFileName();

    protected:
      /**
       * Deletes from memory and cleans up referenced response object.
       *
       */
      void cleanupResponse();

      /**
       * Sets all CURL request options. Returns <code>false</code> when handler can't be
       * properly configured.
       *
       */
      bool prepareCurl();

      /**
       * Cleanups CURL handler.
       *
       */
      void cleanupCurl();

      string url_;
      string method_;
      Response* response_;
      map<string,Cookie*> cookies_;
      Curl* curl_;
      CurlList curlHeaders_;
      string curlPostData_;
      char curlErrorBuffer_[CURL_ERROR_SIZE];
    };
  }
}

#endif /* _MIKE_HTTP_REQUEST_H_ */
