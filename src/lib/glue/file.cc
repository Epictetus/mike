#include "lib/glue/file.h"
#include <sys/stat.h>

namespace mike {
  namespace glue {
    namespace file
    {
      using namespace v8;
      using namespace std;

      namespace
      {
	bool file_exists_p(string fname)
	{
	  struct stat fileinfo;
	  int result = stat(fname.c_str(), &fileinfo);
	  return result == 0 ? true : false;
	}
      }

      /*
       * Function is checking if given file exists. Example (js):
       * 
       *   File.exists("/path/to/file"); // => true or false
       * 
       */
      Handle<Value> exists(const Arguments &args)
      {
	if (args.Length() == 1) {
	  String::Utf8Value fname(args[0]->ToString());
	  return file_exists_p(*fname) ? True() : False();
	} else {
	  return Null();
	}
      }
    }

    /*
     * Returns V8 object placeholder for all file related methods.
     *
     */
    Handle<Object> FileObject()
    {
      HandleScope scope;
      Handle<Object> fileobj(Object::New());

      fileobj->Set(String::NewSymbol("exists"), FunctionTemplate::New(file::exists)->GetFunction());

      return fileobj;
    }
  }
}
