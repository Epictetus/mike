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
    }
    
    /*
     * Returns V8 object placeholder for all file related methods.
     *
     */
    Handle<Object> SystemObject()
    {
      HandleScope scope;
      Handle<Object> systemobj(Object::New());

      systemobj->Set(String::NewSymbol("pwd"), FunctionTemplate::New(system::pwd)->GetFunction());

      return systemobj;
    }
  }
}
