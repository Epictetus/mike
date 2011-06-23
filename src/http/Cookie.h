#ifndef _MIKE_HTTP_COOKIE_
#define _MIKE_HTTP_COOKIE_

#include <string>
#include <time.h>

namespace mike
{
  using namespace std;
  
  class Cookie
  {
  public:
    /**
     * Constructor.
     *
     */
    explicit Cookie(string name, string value, string domain, string path, bool secure, time_t expires);

    /**
     * Destructor.
     *
     */
    ~Cookie();

    string toStr();

    string getName();

    string getValue();

    string getDomain();

    string getPath();

    bool isSecure();

    time_t getExpires();

  protected:
    string name_;
    string value_;
    string domain_;
    string path_;
    bool secure_;
    time_t expires_;
  };
}

#endif /* _MIKE_HTTP_COOKIE_ */
