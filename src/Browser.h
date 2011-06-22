#ifndef _MIKE_BROWSER_H_
#define _MIKE_BROWSER_H_

#include <string>

namespace mike
{
  using namespace std;
  
  class Browser
  {
  public:
    /**
     * Constructor.
     *
     */
    explicit Browser(string language="en", string userAgent="", bool enableCookie=true, bool enableJava=true);

    /**
     * Destructor.
     *
     */
    ~Browser();

    /**
     * Returns browser language.
     *
     */
    string getLanguage();

    /**
     * Returns default user agent assigned to browser.
     *
     */
    string getUserAgent();

    /**
     * Returns <code>true</code> when javascript is enabled. 
     *
     */
    bool isJavaEnabled();

    /**
     * Returns <code>true</code> when cookies are enabled.
     *
     */
    bool isCookieEnabled();

  protected:
    bool javaEnabled_;
    bool cookieEnabled_;
    string language_;
    string customUserAgent_;
  };
}

#endif /* _MIKE_BROWSER_H_ */
