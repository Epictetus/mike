#ifndef _MIKE_HTTP_RESPONSE_H_
#define _MIKE_HTTP_RESPONSE_H_

#include <map>
#include <list>
#include <string>
#include <sstream>

namespace mike {
  namespace http
  {
    using namespace std;

    /**
     * HTTP response handler. Shouldn't be used directly anywhere, should be accessed
     * from the inside of request object. 
     */
    class Response
    {
    public:
      /**
       * Creates new response.
       *
       * \param code HTTP response code.
       * \param content Stream with response body.
       * \param headers Map of HTTP header's keys and values.
       * \param content_type Response content type.
       */
      Response(long code, stringstream* content, map<string,string> headers, string content_type);

      /**
       * Destructor.
       */
      ~Response();

      /**
       * \return HTTP response code.
       */
      long getCode();

      /**
       * \return Body of requested page.
       */
      string getBody();

      /**
       * \return Stream with page content.
       */
      stringstream* getStream();

      /**
       * Returns specified response header.
       *
       * \code
       *   res->getHeader("Referer");
       *   res->getHeader("Accept-Language");
       * \endcode
       *
       * \param key Which header should be returned.
       * \return Specified response header value.
       */
      string getHeader(string key);

      /**
       * \return Content type of requested page.
       */
      string getContentType();

      /**
       * \return Whether requested page is an XML document or not.
       */
      bool isXml();

      /**
       * \return Whether requested page is an HTML document or not.
       */
      bool isHtml();

    protected:
      long code_;
      stringstream* content_;
      string contentType_;
      map<string,string> headers_;
    };
  }
}

#endif /* _MIKE_HTTP_RESPONSE_H_ */
