#ifndef _MIKE_HTTP_RESPONSE_H_
#define _MIKE_HTTP_RESPONSE_H_

#include <map>
#include <list>
#include <string>
#include <sstream>
#include "http/Cookie.h"

namespace mike {
  namespace http
  {
    using namespace std;

    /**
     * HTTP response handler. The same as request class it's base for browser's
     * response, and will not be used directly. Shouldn't be also explicitly created
     * from outside of request class. 
     *
     */
    class Response
    {
    public:
      /**
       * Constructor.
       *
       */
      Response(long code, stringstream* content, map<string,string> headers, string content_type);

      /**
       * Destructor.
       *
       */
      ~Response();

      /**
       * Returns HTTP response code.
       *
       */
      long getCode();

      /**
       * Returns body of requested website as string.
       *
       */
      string getBody();

      /**
       * Returns string stream with content of requested website.
       *
       */
      stringstream* getStream();

      /**
       * Returns specified response header. Example:
       *
       * <code>
       *   res->getHeader("Referer");
       *   res->getHeader("Accept-Language");
       * </code>
       *
       */
      string getHeader(string key);

      /**
       * Returns list of cookies set for this response.
       *
       */
      map<string,Cookie*> getCookies();

      /**
       * Returns cookie object for specified key.
       *
       */
      Cookie* getCookie(string key);

      /**
       * Returns content type of requested website extracted from response headers.
       * 
       */
      string getContentType();

      /**
       * Returns <code>true</code> if requested website is an XML document.
       *
       */
      bool isXml();

      /**
       * Returns <code>true</code> if requested website is an HTML document. 
       *
       */
      bool isHtml();

    protected:
      long code_;
      stringstream* content_;
      string contentType_;
      map<string,string> headers_;
      string cookieString_;
      map<string,Cookie*> cookies_;
    };
  }
}

#endif /* _MIKE_HTTP_RESPONSE_H_ */
