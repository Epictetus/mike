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
      static Handle<Value> JS_GetWindow(Local<String> name, const AccessorInfo& info);

      // Methods
      static Handle<Value> JS_Alert(const Arguments& args);
      static Handle<Value> JS_Confirm(const Arguments& args);
    };
  }
}

#endif /* _MIKE_JAVSASCRIPT_WINDOW_WRAP_H_ */
