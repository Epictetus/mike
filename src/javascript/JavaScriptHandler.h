#ifndef _MIKE_JAVASCRIPT_HANDLER_H_
#define _MIKE_JAVASCRIPT_HANDLER_H_

#include <assert.h>
#include <string>
#include <v8.h>

namespace mike
{
  using namespace std;
  using namespace v8;
  
  class HtmlPage;
  class HtmlElement;

  class JavaScriptObjectWrap
  {
  };

  class JavaScriptHandler
  {
  public:
    template <typename T> static inline void WrapPtr(Handle<Object> handle,T* ptr)
    {
      assert(!handle.IsEmpty());
      assert(handle->InternalFieldCount() > 0);
      handle->SetInternalField(0, External::New((void*)ptr));
    }
  
    JavaScriptHandler(HtmlPage* page);
    ~JavaScriptHandler();

    string evaluate(string source, string fname, unsigned int line);
    
  protected:
    HtmlPage* page_;
    Persistent<Context> context_;
  };
}

#endif /* _MIKE_JAVASCRIPT_HANDLER_H_ */
