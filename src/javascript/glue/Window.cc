#include <list>
#include "javascript/glue/Window.h"
#include "Browser.h"
#include "Window.h"

namespace mike {
  namespace glue
  {
    Handle<FunctionTemplate> Window::BuildTemplate()
    {
      Handle<FunctionTemplate> t = FunctionTemplate::New();
      t->SetClassName(String::New("DOMWindow"));

      // Prototype
      Handle<Template> proto_t = t->PrototypeTemplate();
      proto_t->Set(String::New("alert"), FunctionTemplate::New(JS_Alert));

      // Instance
      Handle<ObjectTemplate> instance_t = t->InstanceTemplate();
      instance_t->SetInternalFieldCount(2);
      instance_t->SetAccessor(String::New("window"), JS_GetWindow);

      return t;
    }

    Handle<Value> Window::JS_GetWindow(Local<String> name, const AccessorInfo& info)
    {
      // window == this, so we can't return `info.Holder()` or `info.This()`, since
      // they are just prototypes of he global obj.
      assert(info.Holder()->InternalFieldCount() > 0);
      return info.Holder()->GetInternalField(0);
    }

    mike::Window* unwrap(Handle<Object> handle)
    {
      Handle<Object> global = Handle<Object>::Cast(handle->GetPrototype());
      assert(global->InternalFieldCount() > 1);
      return (mike::Window*)External::Unwrap(global->GetInternalField(1));
    }
    
    Handle<Value> Window::JS_Alert(const Arguments& args)
    {
      HandleScope scope;
      mike::Window* window = unwrap(args.Holder());
      string message;
      
      if (args.Length() > 0) {
	String::Utf8Value str(args[0]->ToString());
	message = *str;
      }
      
      // Pick up expectation defined in browser.
      list<PopupExpectation>& expects = window->getBrowser()->expectedPopups_;

      // Check if browser was expecting this alert.
      if (!expects.empty()) {
	PopupExpectation e = expects.front();
	expects.pop_front();

	if (e.kind == kPopupAlert) {
	  bool match_msg = e.flags & kMatchMessage == kMatchMessage;

	  if (!match_msg || (args.Length() > 0 && e.message == message))
	    return Undefined();
	}
      }

      // Throw v8 exception to disallow to continue execution.
      Handle<Object> err(Object::New());
      err->SetHiddenValue(String::New("expectation"), Integer::New(kPopupAlert));
      err->SetHiddenValue(String::New("message"), String::New(message.c_str()));
      ThrowException(err);
    }
    
  }
}
