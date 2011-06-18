#ifndef _MIKE_HTTP_RESPONSE_H_
#define _MIKE_HTTP_RESPONSE_H_

#include <map>
#include <string>

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
      Response(long code, string body, map<string,string> headers);

      /**
       * Destructor.
       *
       */
      virtual ~Response();

      /**
       * Returns HTTP response code.
       *
       */
      long getCode();

      /**
       * Returns content of requested website.
       *
       */
      string getBody();

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
      string body_;
      map<string,string> headers_;
    };
  }
}

#endif /* _MIKE_HTTP_RESPONSE_H_ */
