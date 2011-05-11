#include "core/script.h"

namespace mike {
  namespace script
  {
    using namespace v8;
    using namespace std;

    Info::Info(string src, string fname)
    {
      source = src;
      name = fname;
      error = seNone;
    }

    Info::~Info()
    {
      result.Dispose();
    }

    /*
     * Executes given script and returns all information about it wrapped by
     * <code>mike::script::Info</code> struct.
     *
     *   mike::script::Info *info = mike::script::Run("var a=1; a+1", "<eval>");
     *
     *   info->source; // => "var a=1; a+1"
     *   info->name;   // => "<eval>"
     *   info->result; // => v8 handle to result
     *   info->error;  // => seNone
     *
     */
    Info* Run(string src, string fname)
    {
      HandleScope scope;
  
      Local<String> source = String::New(src.c_str());
      Local<String> name = String::New(fname.c_str());
      
      Info *data = new Info(src, fname);

      TryCatch try_catch;
      Local<Script> script = Script::Compile(source, name);
      
      if (try_catch.HasCaught()) {
	data->error = seCompileError;
      } else {
	data->result = Persistent<Value>::New(script->Run());

	if (try_catch.HasCaught()) {
	  data->error = seRuntimeError;
	}
      }

      return data;
    }
  }
}
