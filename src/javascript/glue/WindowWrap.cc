#include "javascript/glue/WindowWrap.h"
#include "Browser.h"
#include "Window.h"

namespace mike {
  namespace glue
  {
    //============================= HELPERS    ===================================

    Window* WindowWrap::UnwrapWindow(Handle<Object> handle)
    {
      Handle<Object> proto = Handle<Object>::Cast(handle->GetPrototype());
      return Unwrap<Window>(proto);
    }

    Handle<FunctionTemplate> WindowWrap::NewTemplate()
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

    //============================= PROPERTIES ===================================
    
    Handle<Value> WindowWrap::JS_GetWindow(Local<String> name, const AccessorInfo& info)
    {
      // window == this, so we can't return `info.Holder()` or `info.This()`, since
      // they are just prototypes of he global obj.
      return Unwrap(info.Holder());
    }

    //============================= METHODS    ===================================

    Handle<Value> WindowWrap::JS_Alert(const Arguments& args)
    {
      HandleScope scope;
      string message;
      
      if (args.Length() > 0) {
	String::Utf8Value str(args[0]->ToString());
	message = *str;
      }

      // Pick up expectations defined in browser.
      Window* window = UnwrapWindow(args.Holder());
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
      err->Set(String::New("expectation"), Integer::New(kPopupAlert));
      err->Set(String::New("message"), String::New(message.c_str()));
      ThrowException(err);
    }    
  }
}
