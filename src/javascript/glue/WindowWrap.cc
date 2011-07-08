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
    
    JS_GETTER(WindowWrap, Window)
    {
      // window == this, so we can't return `info.Holder()` or `info.This()`, since
      // they are just prototypes of he global obj.
      return Unwrap(info.Holder());
    }
    JS_END

    //============================= FUNCTIONS  ===================================

    JS_FUNCTION(WindowWrap, Alert)
    {
      JS_ARG_UTF8(message, 0);
      
      // Pick up expectations defined in browser.
      Window* window = UnwrapWindow(args.Holder());
      list<PopupExpectation>& expects = window->getBrowser()->expectedPopups_;

      // Check if browser was expecting this alert.
      if (!expects.empty()) {
	PopupExpectation e = expects.front();
	expects.pop_front();

	if (e.kind == kPopupAlert) {
	  bool match_msg = e.flags & kMatchMessage == kMatchMessage;

	  if (!match_msg || (JS_ARGC > 0 && e.message == message))
	    return JS_UNDEF;
	}
      }

      // If alert was unexpected then throw v8 exception to disallow
      // continue execution.
      Handle<Object> err(JS_OBJ2);
      err->Set(JS_STR("expectation"), JS_INT(kPopupAlert));
      err->Set(JS_STR("message"), JS_STR(message.c_str()));
      JS_THROW_OBJ(err);
    }    
    JS_END

    JS_FUNCTION(WindowWrap, Confirm)
    {
      JS_ARG_UTF8(message, 0);

      // Pick up expectations defined in browser.
      Window* window = UnwrapWindow(args.Holder());
      list<PopupExpectation>& expects = window->getBrowser()->expectedPopups_;

      // Check if browser was expecting this confirmation.
      if (!expects.empty()) {
	PopupExpectation e = expects.front();
	expects.pop_front();

	if (e.kind == kPopupConfirm) {
	  bool match_msg = e.flags & kMatchMessage == kMatchMessage;

	  if (!match_msg || (JS_ARGC > 0 && e.message == message))
	    return JS_BOOL(e.choice);
	}
      }

      // If confirmation was unexpected then throw v8 exception to disallow
      // continue execution.
      Handle<Object> err(JS_OBJ2);
      err->Set(JS_STR("expectation"), JS_INT(kPopupConfirm));
      err->Set(JS_STR("message"), JS_STR(message.c_str()));
      JS_THROW_OBJ(err);
    }
    JS_END
  }
}
