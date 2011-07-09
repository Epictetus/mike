#include <assert.h>

#include "javascript/JavaScriptHandler.h"
#include "html/HtmlPage.h"
#include "html/HtmlElement.h"
#include "Browser.h"

#include "javascript/glue/WindowWrap.h"

namespace mike
{
  JavaScriptHandler::JavaScriptHandler(HtmlPage* page)
  {
    HandleScope scope;
    page_ = page;

    // Setting up new context with window object as a global.
    Handle<FunctionTemplate> window_tpl = glue::WindowWrap::NewTemplate();
    context_ = Context::New(NULL, window_tpl->InstanceTemplate());
    
    Handle<Object> global_instance = context_->Global();
    Handle<Object> global_proto = Handle<Object>::Cast(global_instance->GetPrototype());

    // Wrap enclosing window within global object.
    glue::ObjectWrap::Wrap<Window>(global_proto, page_->getEnclosingWindow(), 0);
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
	  page_->getEnclosingWindow()->getBrowser()->clearExpectations();
	  
	  if (!exp.IsEmpty()) {
	    int exp_type = exp->Get(String::New("expectation"))->Int32Value();
	    String::Utf8Value str(exp->Get(String::New("message"))->ToString());
	    string exp_msg = *str;

	    switch (exp_type) {
	    case kPopupAlert:
	      throw UnexpectedAlertError(exp_msg);
	    case kPopupConfirm:
	      throw UnexpectedConfirmError(exp_msg);
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
