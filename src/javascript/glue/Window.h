#ifndef _MIKE_JAVSASCRIPT_GLUE_WINDOW_H_
#define _MIKE_JAVSASCRIPT_GLUE_WINDOW_H_

#include "Window.h"
#include "javascript/glue/Object.h"

namespace mike {
  namespace glue
  {
    class Window : public JsObject
    {
    public:
      static Handle<ObjectTemplate> BuildTemplate();

      // Properties
      static Handle<Value> JS_GetWindow(Local<String> name, const AccessorInfo& info);

      // Methods
      static Handle<Value> JS_Alert(const Arguments& args);
    };
  }
}

#endif /* _MIKE_JAVSASCRIPT_GLUE_WINDOW_H_ */
