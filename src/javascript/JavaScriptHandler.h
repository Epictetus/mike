#ifndef _MIKE_JAVASCRIPT_HANDLER_H_
#define _MIKE_JAVASCRIPT_HANDLER_H_

#include <string>
#include <v8.h>

namespace mike
{
  using namespace std;
  using namespace v8;
  
  class HtmlPage;
  class HtmlElement;
  
  class JavaScriptHandler
  {
  public:
    JavaScriptHandler(HtmlPage* page);
    ~JavaScriptHandler();

    string evaluate(string source, string fname, unsigned int line);
    
  protected:
    HtmlPage* page_;
    Persistent<Context> context_;
  };
}

#endif /* _MIKE_JAVASCRIPT_HANDLER_H_ */
