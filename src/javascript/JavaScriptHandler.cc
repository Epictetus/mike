#include "javascript/JavaScriptHandler.h"
#include "html/HtmlPage.h"
#include "html/HtmlElement.h"

namespace mike
{
  JavaScriptHandler::JavaScriptHandler(HtmlPage* page)
  {
    HandleScope scope;
    page_ = page;
    context_ = Context::New();
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
    } else {
      Handle<Value> result = script->Run();

      if (try_catch.HasCaught()) {
	printf("JS: Runtime error\n");
      } else {
	String::Utf8Value str(result->ToString());
	return *str ? *str : "";
      }
    }
  }
}
