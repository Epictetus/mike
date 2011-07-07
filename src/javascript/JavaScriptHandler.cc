#include <assert.h>

#include "javascript/JavaScriptHandler.h"
#include "html/HtmlPage.h"
#include "html/HtmlElement.h"

#include "javascript/glue/Window.h"

namespace mike
{
  JavaScriptHandler::JavaScriptHandler(HtmlPage* page)
  {
    HandleScope scope;
    page_ = page;

    // Setting up new context with window object as a global.
    Handle<ObjectTemplate> global_tpl = glue::Window::BuildTemplate();
    context_ = Context::New(NULL, global_tpl);

    // We have to get global object prototype, because this object is passed as
    // a holder to all function calls. Only this way we can access data from the
    // internal fields.
    Handle<Object> global = Handle<Object>::Cast(context_->Global()->GetPrototype());

    // Now we need to current enclosing window in js window internal field.
    WrapPtr<Window>(global, page_->getEnclosingWindow());
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
