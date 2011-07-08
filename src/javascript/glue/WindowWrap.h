#ifndef _MIKE_JAVSASCRIPT_WINDOW_WRAP_H_
#define _MIKE_JAVSASCRIPT_WINDOW_WRAP_H_

#include "javascript/glue/ObjectWrap.h"

namespace mike
{
  class Window;
  class Browser;
  
  namespace glue
  {
    class WindowWrap : public ObjectWrap
    {
    public:
      static Window* UnwrapWindow(Handle<Object> handle);
      static Handle<FunctionTemplate> NewTemplate();

      // Properties

      JS_GETTER_D(Window);

      // Functions
      
      JS_FUNCTION_D(Alert);
      JS_FUNCTION_D(Confirm);
    };
  }
}

#endif /* _MIKE_JAVSASCRIPT_WINDOW_WRAP_H_ */
