#include "mike/script.h"

namespace mike
{
  using namespace v8;
  using namespace std;
  
  Script::Script(int error, string src, std::string fname)
  {
    this->errorCode = error;
    this->source = src;
    this->fileName = fname;
  }
  
  Script::Script(Handle<Value> result, string src, string fname)
  {
    HandleScope scope;
    
    this->result = Persistent<Value>::New(result);
    this->errorCode = 0;
    this->source = src;
    this->fileName = fname;
  }

  Script::~Script()
  {
    result.Dispose();
  }

  Script* Script::Run(string src, string fname)
  {
    HandleScope scope;
    TryCatch try_catch;
  
    Local<String> source = String::New(src.c_str());
    Local<String> name = String::New(fname.c_str());
    Local<v8::Script> script = v8::Script::Compile(source, name);
      
    if (try_catch.HasCaught()) {
      return new Script(JS_COMPILE_ERROR, src, fname);
    } else {
      Handle<Value> result = script->Run();

      if (try_catch.HasCaught()) {
	return new Script(JS_RUNTIME_ERROR, src, fname);
      } else {
	return new Script(result, src, fname);
      }
    }
  }

  bool Script::HasErrors()
  {
    return errorCode == 0 ? false : true; 
  }

  string Script::Source()
  {
    return source;
  }

  string Script::FileName()
  {
    return fileName;
  }

  int Script::ErrorCode()
  {
    return errorCode;
  }

  Handle<Value> Script::Result()
  {
    return result;
  }
}
