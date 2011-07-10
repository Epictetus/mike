#include "javascript/glue/WindowWrap.h"
#include "Browser.h"
#include "Window.h"

namespace mike {
  namespace glue
  {
    //============================= BUILDER    ===================================

    Handle<FunctionTemplate> WindowWrap::NewTemplate()
    {
      Handle<FunctionTemplate> t = JS_FUNC_TPL();
      t->SetClassName(JS_STR("DOMWindow"));

      // Prototype
      Handle<Template> proto_t = t->PrototypeTemplate();
      proto_t->Set(JS_STR("alert"), JS_FUNC_TPL(JS_Alert));
      proto_t->Set(JS_STR("confirm"), JS_FUNC_TPL(JS_Confirm));

      // Instance
      Handle<ObjectTemplate> instance_t = t->InstanceTemplate();
      instance_t->SetInternalFieldCount(1);
      instance_t->SetAccessor(JS_STR("window"), JS_GetWindow);

      return t;
    }

    //============================= PROPERTIES ===================================
    
    JS_GETTER(WindowWrap, Window) // window
    {
      // window == this, so we can't return `info.Holder()` or `info.This()`, since
      // they are just prototypes of the global obj. Global object have to be returned
      // directly here.
      return JS_GLOBAL;
    }
    JS_END

    //============================= FUNCTIONS  ===================================

    JS_FUNCTION(WindowWrap, Alert) // alert(msg)
    {
      JS_ARG_UTF8(message, 0);
      
      // Pick up expectations defined in browser.
      list<PopupExpectation>& expects = GetWindow()->getBrowser()->expectedPopups_;

      // Check if browser was expecting this alert.
      if (!expects.empty()) {
	PopupExpectation e = expects.front();
	expects.pop_front();

	if (e.kind == kPopupAlert) {
	  bool match_msg = (e.flags & kMatchMessage) == kMatchMessage;

	  if (!match_msg || (JS_ARGC > 0 && e.message == message))
	    return JS_UNDEF;
	}
      }

      // If alert was unexpected then throw v8 exception to disallow
      // continue execution.
      Handle<Object> err(JS_OBJ());
      err->Set(JS_STR("expectation"), JS_INT(kPopupAlert));
      err->Set(JS_STR("message"), JS_STR(message.c_str()));
      
      JS_THROW_OBJ(err);
    }    
    JS_END

    JS_FUNCTION(WindowWrap, Confirm) // confirm(msg)
    {
      JS_ARG_UTF8(message, 0);

      // Pick up expectations defined in browser.
      list<PopupExpectation>& expects = GetWindow()->getBrowser()->expectedPopups_;

      // Check if browser was expecting this confirmation.
      if (!expects.empty()) {
	PopupExpectation e = expects.front();
	expects.pop_front();

	if (e.kind == kPopupConfirm) {
	  bool match_msg = (e.flags & kMatchMessage) == kMatchMessage;

	  if (!match_msg || (JS_ARGC > 0 && e.message == message))
	    return JS_BOOL(e.choice);
	}
      }

      // If confirmation was unexpected then throw v8 exception to disallow
      // continue execution.
      Handle<Object> err(JS_OBJ());
      err->Set(JS_STR("expectation"), JS_INT(kPopupConfirm));
      err->Set(JS_STR("message"), JS_STR(message.c_str()));

      JS_THROW_OBJ(err);
    }
    JS_END
  }
}
