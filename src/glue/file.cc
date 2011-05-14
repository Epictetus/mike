#include "glue/file.h"
#include <sys/stat.h>
#include <fstream>
#include <sstream>
#include <string>

namespace mike {
  namespace glue {
    namespace file
    {
      using namespace v8;
      using namespace std;

      bool exists_p(string fname)
      {
	struct stat fileinfo;

	if (access(fname.c_str(), 0) == 0) {
	  return (stat(fname.c_str(), &fileinfo) == 0);
	}

	return false;
      }

      bool check_st_mode(string fname, int mode)
      {
	struct stat fileinfo;
	bool result = false;
	  
	if (access(fname.c_str(), 0) == 0) {
	  if (stat(fname.c_str(), &fileinfo) == 0) {
	    return fileinfo.st_mode & mode;
	  }
	}

	return false;
      }

      bool read_contents(string *content, string fname)
      {
	ifstream fp(fname.c_str());

	if (fp.is_open()) {
	  stringstream buffer;
	  buffer << fp.rdbuf();
	  fp.close();
	  *content = buffer.str();
	  return true;
	}

	return false;
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
	  return exists_p(*fname) ? True() : False();
	} else {
	  return Undefined();
	}
      }

      /*
       * This function is checking if given path represents directory. If
       * 
       *   File.isDirectory("/path/to/file"); // => true or false
       *
       */
      Handle<Value> isDirectory(const Arguments &args)
      {
	if (args.Length() == 1) {
	  String::Utf8Value fname(args[0]->ToString());
	  return check_st_mode(*fname, S_IFDIR) ? True() : False();
	} else {
	  return Undefined();
	}
      }

      /*
       * This function is checking if given path represents file. If
       * 
       *   File.isFile("/path/to/file"); // => true or false
       *
       */
      Handle<Value> isFile(const Arguments &args)
      {
	if (args.Length() == 1) {
	  String::Utf8Value fname(args[0]->ToString());
	  return check_st_mode(*fname, S_IFREG) ? True() : False();
	} else {
	  return Undefined();
	}
      }

      /*
       * Reads contents from specified file. If it's unable to read given file
       * then <code>null</code> is returned. 
       *
       *   File.read("/path/to/file"); // contents or null
       *
       */
      Handle<Value> read(const Arguments &args)
      {
	if (args.Length() == 1) {
	  String::Utf8Value fname(args[0]->ToString());
	  string content;
	  if (read_contents(&content, *fname)) {
	    return String::New(content.c_str());
	  } else {
	    return Null();
	  }
	} else {
	  return Undefined();
	}
      }
    }

    Handle<Object> FileObject()
    {
      Handle<Object> fileobj(Object::New());

      fileobj->Set(String::NewSymbol("exists"), FunctionTemplate::New(file::exists)->GetFunction());
      fileobj->Set(String::NewSymbol("isDirectory"), FunctionTemplate::New(file::isDirectory)->GetFunction());
      fileobj->Set(String::NewSymbol("isFile"), FunctionTemplate::New(file::isFile)->GetFunction());
      fileobj->Set(String::NewSymbol("read"), FunctionTemplate::New(file::read)->GetFunction());

      return fileobj;
    }
  }
}
