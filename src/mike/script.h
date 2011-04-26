#ifndef _MIKE_SCRIPT_H_
#define _MIKE_SCRIPT_H_

#include "mike.h"

namespace mike
{
  using namespace v8;
  using namespace std;
  
  class Script
  {
    string source;
    string fileName;
    int errorCode;
    Persistent<Value> result;
  public:
    Script(int error, string src, string fname);
    Script(Handle<Value> result, string src, string fname);
    ~Script();
    bool HasErrors();
    string Source();
    string FileName();
    int ErrorCode();
    Handle<Value> Result();
    static Script* Run(string src, string fname);
  };
}

#define JS_COMPILE_ERROR 1
#define JS_RUNTIME_ERROR 2

#endif /* _MIKE_SCRIPT_H_ */
