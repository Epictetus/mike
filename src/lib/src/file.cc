#include "lib/src/file.h"
#include <sys/stat.h>

namespace mike {
  namespace glue {
    namespace file {
      using namespace v8;
      using namespace std;

      namespace {
	bool file_exists_p(string fname)
	{
	  struct stat fileinfo;
	  int result = stat(fname.c_str(), &fileinfo);
	  return result == 0 ? true : false;
	}
      }
      
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
  }
}
