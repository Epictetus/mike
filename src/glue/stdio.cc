#include "glue/stdio.h"

namespace mike {
  namespace glue {
    namespace stdio
    {
      using namespace std;
      using namespace v8;
      
      /*
       * Writes given text to standard outuput stream. 
       *
       *   $stdout.write("popatrz jaka franca!\n");
       *   $stdout.write("foo", "bar\n");
       *
       */
      Handle<Value> stdoutWrite(const Arguments &args)
      {
	for (int i = 0; i < args.Length(); i++) {
	  String::Utf8Value text(args[i]->ToString());
	  fprintf(stdout, "%s", *text);
	}
	return Null();
      }

      /*
       * Writes given text to standard error stream. 
       *
       *   $stderr.write("wskoczyl by mi do tego!\n");
       *   $stderr.write("forfiter", "szwagier\n");
       *
       */
      Handle<Value> stderrWrite(const Arguments &args)
      {
	for (int i = 0; i < args.Length(); i++) {
	  String::Utf8Value text(args[i]->ToString());
	  fprintf(stderr, "%s", *text);
	}
	return Null();
      }
    }

    Handle<Object> StdoutObject()
    {
      Handle<Object> stdoutobj(Object::New());
      stdoutobj->Set(String::NewSymbol("write"), FunctionTemplate::New(stdio::stdoutWrite)->GetFunction());
      return stdoutobj;

    }

    Handle<Object> StderrObject()
    {
      Handle<Object> stderrobj(Object::New());
      stderrobj->Set(String::NewSymbol("write"), FunctionTemplate::New(stdio::stderrWrite)->GetFunction());
      return stderrobj;
    }
  }
}
