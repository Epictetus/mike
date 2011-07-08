#include <assert.h>

#include "javascript/JavaScriptHandler.h"
#include "html/HtmlPage.h"
#include "html/HtmlElement.h"
#include "Browser.h"

#include "javascript/glue/Window.h"

namespace mike
{
  JavaScriptHandler::JavaScriptHandler(HtmlPage* page)
  {
    HandleScope scope;
    page_ = page;

    // Setting up new context with window object as a global.
    Handle<FunctionTemplate> window_tpl = glue::Window::BuildTemplate();
    context_ = Context::New(NULL, window_tpl->InstanceTemplate());
    
    Handle<Object> global_instance = context_->Global();
    Handle<Object> global_proto = Handle<Object>::Cast(global_instance->GetPrototype());

    // Internal fields have to be set within prototype, beacuse not global object directly,
    // only its proto is passed as This or Holder to properties and functions. 
    global_proto->SetInternalField(0, global_instance);
    global_proto->SetInternalField(1, External::New((void*)page_->getEnclosingWindow()));
  }

  JavaScriptHandler::~JavaScriptHandler()
  {
    context_.Dispose();
  }

  string JavaScriptHandler::evaluate(string source, string fname, unsigned int line)
  {
    HandleScope scope;
    TryCatch try_catch;

    context_->Enter();
  
    Local<String> s = String::New(source.c_str());
    Local<String> n = String::New(fname.c_str());
    
    Local<Script> script = Script::Compile(s, n);
      
    if (try_catch.HasCaught()) {
      printf("JS: Compile error\n");
      return "";
    } else {
      Handle<Value> result = script->Run();

      if (try_catch.HasCaught()) {
	Handle<Value> err = try_catch.Exception();

	if (!err->IsString()) {
	  Handle<Object> exp = Handle<Object>::Cast(err);
	
	  if (!exp.IsEmpty()) {
	    int exp_type = exp->GetHiddenValue(String::New("expectation"))->Int32Value();
	    String::Utf8Value str(exp->GetHiddenValue(String::New("message"))->ToString());
	    string exp_msg = *str;

	    switch (exp_type) {
	    case kPopupAlert:
	      throw UnexpectedAlertError(exp_msg);
	    //case kPopupConfirm:
	    //  throw UnexpectedConfirmError(exp_msg);
	    default:
	      break;
	    }
	  }
	}

	printf("JS: Runtime error\n");
	return "";
      } else {
	String::Utf8Value str(result->ToString());
	return *str ? *str : "";
      }
    }
  }
}
