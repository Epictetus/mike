#ifndef _MIKE_HTTP_REQUEST_H_
#define _MIKE_HTTP_REQUEST_H_

#include <map>
#include <list>
#include <string>
#include <sstream>
#include <exception>
#include <curl/curl.h>

#include "http/Response.h"
#include "http/Headers.h"

namespace mike {
  namespace http
  {
    using namespace std;

    // Friendly names for CURL types.
    typedef CURL Curl;
    typedef CURLcode CurlCode;
    typedef struct curl_slist* CurlList;

    /**
     * Error throwed when requested page can't be reached. 
     */
    class ConnectionError : public exception
    {
    public:
      explicit ConnectionError(string url) : url_(url) {}
      virtual ~ConnectionError() throw() {};
      virtual const char* what() const throw() { return ("Page " + url_ + " can't be reached.").c_str(); }
      virtual const char* url() const { return url_.c_str(); }
    protected:
      string url_;
    };
    
    /**
     * HTTP request class built at top of CURL library. This class rather will
     * not be used directly in code, it's base for browser specific requests.
     *
     * \code
     *   Request* req = Request::Get("http://www.mypage.com");
     *   req->setHeader("Custom-Header: Forfiter");
     *
     *   try {
     *     req->pefrorm());
     *     string content = req->getResponse()->getBody();
     *   } catch (ConnectionError err) {
     *     printf(err->getReason());
     *   } finally {
     *     delete req;
     *   }
     * \endcode
     */
    class Request
    {
    public:
      /**
       * Creates new GET request for given url.
       *
       * \param URL of page to open.
       * \return New request object.
       */
      static Request* Get(string url);

      /**
       * Creates new POST request for given url.
       *
       * \param URL of page to open.
       * \return New request object.
       */
      static Request* Post(string url);

      /**
       * Creates new request.
       *
       * \param URL of page to open.
       * \param HTTP request method.
       */
      Request(string url, string method="GET");

      /**
       * Destructor.
       */
      ~Request();

      /**
       * Sets given custom HTTP header for this request, eg:
       *
       * \code
       *   req->setHeader("Referer: http://www.referersite.com");
       *   req->setHeader("Accept: text/javascript");
       * \endcode
       *
       * \param header HTTP header line to set.
       */
      void setHeader(string header);

      /**
       * Shortcut for setting referer header.
       *
       * \param url Referer page.
       */
      void setReferer(string url);
      
      /**
       * Sets given string as POST data, eg:
       *
       * \code
       *   req->setData("user=forfiter&password=szwagier");
       * \endcode
       *
       * \param data Post data to set.
       */
      void setData(string data);

      /**
       * \return URL for which current request has been created.
       */
      string getUrl() const;

      /**
       * \return Request method defined by constructor.
       */
      string getMethod() const;

      /**
       * Returns HTTP response generated after performing this request. If request
       * has not been performed yet then obviously 'NULL' will be returned.
       *
       * \return Response for this request.
       */
      Response* getResponse();

      /**
       * Performs this request. If requested page is unreachable then throws ConnectionError.
       *
       * \return Response for this request.
       */
      Response* perform();

      /**
       * Enables cookies within encapsulated seession. Session is distinguised by given
       * instance's token.
       *
       * \param enable If false then session will not be enabled.
       * \param token Cookie session token.
       */
      void enableCookieSession(string token);
      void enableCookieSession(bool enable, string token);
      
    protected:
      string url_;
      string method_;
      Response* response_;
      Curl* curl_;
      CurlList curlHeaders_;
      string curlPostData_;
      char curlErrorBuffer_[CURL_ERROR_SIZE];
      string sessionToken_;
      bool cookieEnabled_;

      /**
       * \return Name of file where cookies should be stored.
       */
      string cookieFileName() const;

      /**
       * Deletes from memory and cleans up referenced response object.
       */
      void cleanupResponse();

      /**
       * Sets all CURL request options. Returns 'false' when handler can't be properly configured.
       *
       * \return State of CURL handle preparation.
       */
      bool prepareCurl();

      /**
       * Cleanups CURL handler.
       */
      void cleanupCurl();

    };
  }
}

#endif /* _MIKE_HTTP_REQUEST_H_ */
