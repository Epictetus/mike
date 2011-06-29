#ifndef _MIKE_HTTP_HEADERS_H_
#define _MIKE_HTTP_HEADERS_H_

#include <map>
#include <string>

namespace mike {
  namespace http
  {
    using namespace std;
    
    /**
     * HTTP headers parser and extractor. It's not fully funcitonal HTTP parser,
     * it cooperates with CURL's headers handler defined for request.
     */
    class Headers
    {
    public:
      /**
       * Parses given line and appends extracted header and value to headers map.
       *
       * \code
       *   headers.parseAndAppend("Referer: http://mywebsite.com\r\n");
       *   headers.parseAndAppend("Cookie: cookiestring\r\n");
       * \endcode
       *
       * \param line HTTP headers line to parse.
       */
      void parseAndAppend(string line);

      /**
       * Converts all extracted headers to key/value map.
       *
       * \code
       *   map<string,string> headers_map = headers.toMap();
       * \endcode
       *
       * \return Map of header's keys and values.
       */
      map<string,string> toMap();

      /**
       * Cleans up referenced headers map.
       */
      void clear();

    protected:
      map<string,string> headers_;
    };
  }
}

#endif /* _MIKE_HTTP_HEADERS_H_ */
