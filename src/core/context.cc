#include <sys/stat.h>
#include "core/context.h"
#include "glue/file.h"
#include "unistd.h"

namespace mike {
  namespace context
  {
    using namespace v8;
    using namespace std;

    namespace {
      /*
       * Caller for <code>Window::Require</code> method. Requires specified module and returns
       * it's exports. Examples:
       *
       *   assert = require('assert');
       *   assert.ok(true, "should be true!");
       *
       */
      Handle<Value> require(const Arguments &args)
      {
	HandleScope scope;
      
	if (args.Length() == 1 && !args.Data().IsEmpty() && args.Data()->IsExternal()) {
	  Window *window = (Window*)External::Cast(*args.Data())->Value();
	  String::Utf8Value module(args[0]->ToString());
	  return window->Require(*module);
	}
      
	return Undefined();
      }
    }
    
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
      glue::Splice(context);
      SpliceRequire();
      Require("core");
    }

    Window::~Window()
    {
      for (list<script::Info*>::iterator it = results.begin(); it != results.end(); it++) {
	delete *it;
      }
      
      context.Dispose();
    }
    
    void Window::SpliceRequire()
    {
      HandleScope scope;
      Handle<FunctionTemplate> tpl = FunctionTemplate::New(require, External::New((void*)this));
      context->Global()->Set(String::NewSymbol("require"), tpl->GetFunction());
    }

    /*
     * Requires specified module from mike's load path.
     *
     * TODO: some exceptions?
     */
    Handle<Value> Window::Require(string module)
    {
      HandleScope scope;
      Handle<Array> loadpath = LoadPath();
      
      for (int i = 0; i < loadpath->Length(); i++) {
	String::Utf8Value path(loadpath->Get(i)->ToString());
	string filename = string(*path) + "/" + module + ".js"; // TODO: maybe some join here?
	
	if (glue::file::check_st_mode(filename, S_IFREG)) {
	  char *content = glue::file::read_contents((char*)filename.c_str());
	  
	  if (content != NULL) {
	    script::Info *info = Evaluate(content, filename);
	    return info->result;
	  }
	}
      }
      
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
      if (!Context::InContext() || Context::GetEntered() != context) {
	context->Enter();
      }
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
    script::Info* Window::Evaluate(string src, string fname/*= "<eval>"*/)
    {
      HandleScope scope;
      EnterContext();
      script::Info* info = script::Run(src, fname);
      results.push_back(info);
      return info;
    }

    /*
     * Returns <code>script::Info</code> object for the last executed script.
     *
     */
    script::Info* Window::LastExecutedScript()
    {
      if (results.empty()) {
	return NULL;
      } else {
	return results.back();
      }
    }
  }
}
