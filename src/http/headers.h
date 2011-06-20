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
     * it cooperates with CURL's headers handler defined in request.
     *
     */
    class Headers
    {
    public:
      /**
       * Constructor.
       *
       */
      Headers();

      /**
       * Destructor.
       *
       */
      ~Headers();

      /**
       * Parses given line and appends extracted header and value to headers map.
       *
       * <code>
       *   headers.parseAndAppend("Referer: http://mywebsite.com\r\n");
       *   headers.parseAndAppend("Cookie: cookiestring\r\n");
       * </code>
       *
       */
      void parseAndAppend(string line);

      /**
       * Returns all extracted headers as key/value map.
       *
       * <code>
       *   map<string,string> headers_map = headers.toMap();
       * </code>
       *
       */
      map<string,string> toMap();

      /**
       * Cleans up referenced headers map.
       *
       */
      void clear();

    protected:
      map<string,string> headers_;
    };
  }
}

#endif /* _MIKE_HTTP_HEADERS_H_ */
