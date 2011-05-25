#include <assert.h>
#include <unistd.h>

#include "mike/utils/test.h"

using namespace v8;
using namespace std;

Handle<Value> JsPrint(const Arguments &args);
Handle<Value> JsPuts(const Arguments &args);


int main(int argc, char **argv)
{
  chdir("jstest");
  HandleScope scope;

  Handle<ObjectTemplate> global = ObjectTemplate::New();
  global->Set(String::NewSymbol("print"), FunctionTemplate::New(JsPrint));
  global->Set(String::NewSymbol("puts"), FunctionTemplate::New(JsPuts));
    
  Persistent<Context> cxt = Context::New(NULL, global);
  cxt->Enter();

  mike::TestingEvalFile("suite/prepare.js");
  mike::TestingEvalFile("test-foo.js");
  
  return mike::TestingEvalFile("suite/run.js") ? 0 : 1;
}

Handle<Value> JsPrint(const Arguments &args)
{
  HandleScope scope;
  
  for (int i = 0; i < args.Length(); i++) {
    String::Utf8Value str(args[i]);
    printf("%s", *str);
  }

  return Null();
}

Handle<Value> JsPuts(const Arguments &args)
{
  HandleScope scope;
  JsPrint(args);
  printf("\n");
  return Null();
}
