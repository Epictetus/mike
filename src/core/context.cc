#include <sys/stat.h>
#include "core/context.h"
#include "glue/glue.h"
#include "glue/file.h"
#include "unistd.h"
#include "stdio.h"

namespace mike {
  namespace context
  {
    using namespace v8;
    using namespace std;
    
    /*
     * Creates and returns new Window context.
     *
     */
    Window* New()
    {
      return new Window();
    }

    Window::Window()
    {
      HandleScope scope;
      context = v8::Context::New();
      context->Enter();
      glue::Splice(this, context->Global());
      Require("core");
    }

    Window::~Window()
    {
      context.Dispose();
    }
    
    /*
     * Requires specified module from mike's load path.
     *
     * TODO: some exceptions?
     */
    Handle<Value> Window::Require(string module)
    {
      Handle<Array> loadpath = LoadPath();
      
      for (int i = 0; i < loadpath->Length(); i++) {
	String::Utf8Value path(loadpath->Get(i)->ToString());
	string filename = string(*path) + "/" + module + ".js";
	
	if (glue::file::check_st_mode(filename, S_IFREG)) {
	  string content;
	  
	  if (glue::file::read_contents(&content, filename) && content != "") {
	    return Evaluate(content, filename);
	  }
	}
      }

      ThrowException(Exception::Error(String::New(("no such module to load -- " + module).c_str())));
      return Undefined();
    }
      
    /*
     * Returns v8 array with system load paths. 
     *
     */
    Handle<Array> Window::LoadPath()
    {
      return (Handle<Array>)Array::Cast(*context->Global()->Get(String::NewSymbol("$LOAD_PATH")));
    }

    /*
     * Enters into v8 context if necessary. If context is already entered it
     * does nothing. 
     *
     */
    void Window::EnterContext()
    {
      
    }

    /*
     * Evaluates given javascript source within global window context and
     * returns <code>mike::script::Info</code> struct with result and info. 
     * 
     *   mike::context::Window *window = mike::context::New();
     *   window->Evaluate("var a=1;");
     *   window->Evaluate("var b=a+1;");
     *   delete window;
     *
     */
    Handle<Value> Window::Evaluate(string src, string fname/*= "<eval>"*/)
    {
      if (!Context::InContext() || Context::GetEntered() != context) {
	context->Enter();
      }

      Handle<String> source = String::New(src.c_str());
      Handle<String> name = String::New(fname.c_str());
      
      TryCatch try_catch;
      Handle<Script> script = Script::Compile(source, String::New("<eval>"));
      
      if (try_catch.HasCaught()) {
	// error...
      } else {
	Handle<Value> result = script->Run();

	if (try_catch.HasCaught()) {
	  // error...
	} else {
	  return result;
	}
      }

      return Handle<Value>();
    }
  }
}
