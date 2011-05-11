#include "lib/glue/system.h"
#include <unistd.h>
#include <sys/param.h>
#include <string>

namespace mike {
  namespace glue {
    namespace system
    {
      using namespace v8;
      using namespace std;

      /*
       * Returns path to current working directory. 
       *
       *   System.pwd(); // current path
       *
       */
      Handle<Value> pwd(const Arguments &args)
      {
	char path[MAXPATHLEN];
	getcwd(path, MAXPATHLEN);
	return String::New(path);
      }

      /*
       * Changes current working directory to specified one. 
       *
       *   System.cwd("/new/working/dir"); // true or false
       *
       */
      Handle<Value> cwd(const Arguments &args)
      {
	if (args.Length() == 1) {
	  String::Utf8Value path(args[0]->ToString());

	  if (chdir(*path) == 0) {
	    return True();
	  } 
	}
	return False();
      }
    }
    
    Handle<Object> SystemObject()
    {
      HandleScope scope;
      Handle<Object> systemobj(Object::New());

      systemobj->Set(String::NewSymbol("pwd"), FunctionTemplate::New(system::pwd)->GetFunction());
      systemobj->Set(String::NewSymbol("cwd"), FunctionTemplate::New(system::cwd)->GetFunction());

      return systemobj;
    }
  }
}
