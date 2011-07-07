#include "javascript/glue/Window.h"
#include "Browser.h"

namespace mike {
  namespace glue
  {
    Handle<ObjectTemplate> Window::BuildTemplate()
    {
      Handle<ObjectTemplate> tpl = ObjectTemplate::New();
      tpl->SetInternalFieldCount(1);

      // Window properties...
      tpl->SetAccessor(String::NewSymbol("window"), JS_GetWindow);

      return tpl;
    }

    Handle<Value> Window::JS_GetWindow(Local<String> name, const AccessorInfo& info)
    {
      assert(Context::InContext());
      // window == this, so we can't return info.Holder or info.This, since they are
      // just prototypes of he global obj. Global object from the currently entered
      // context have to be returned.
      return Context::GetEntered()->Global();
    }

    Handle<Value> Window::JS_Alert(const Arguments& args)
    {
      
    }
  }
}
