#include "glue/glue.h"
#include "glue/file.h"
#include "glue/system.h"
#include "glue/stdio.h"

namespace mike {
  namespace glue
  {
    using namespace std;
    using namespace v8;

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
      if (args.Length() == 1 && !args.Data().IsEmpty() && args.Data()->IsExternal()) {
	context::Window *window = (context::Window*)External::Cast(*args.Data())->Value();
	String::Utf8Value module(args[0]->ToString());
	return window->Require(*module);
      }
      return Undefined();
    }

    /*
     * Registers whole stuff provided by native code within given context. 
     *
     */
    void Splice(context::Window *window, Handle<Object> global)
    {
      Handle<Object> mike(Object::New());
      
      // Native objects
      mike->Set(String::NewSymbol("Stdout"), StdoutObject());
      mike->Set(String::NewSymbol("Stderr"), StderrObject());
      mike->Set(String::NewSymbol("File"), FileObject());
      mike->Set(String::NewSymbol("System"), SystemObject());
 
      // Require funciton
      Handle<FunctionTemplate> tpl = FunctionTemplate::New(require, External::New((void*)window));
      mike->Set(String::NewSymbol("require"), tpl->GetFunction());

      // Registering Mike's namespace
      global->Set(String::NewSymbol("$mike"), mike);
      
      // Load path
      Handle<Array> loadpath(Array::New());
      loadpath->Set(0, String::New(MIKE_LIBDIR));
      global->Set(String::NewSymbol("$LOAD_PATH"), loadpath);
    }
  }
}
