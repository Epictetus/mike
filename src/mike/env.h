#ifndef _MIKE_ENV_H_
#define _MIKE_ENV_H_

#include "mike.h"
#include "mike/script.h"
#include "mike/stdio.h"
#include "mike/script.h"

namespace mike
{
  using namespace v8;
  using namespace std;
  
  class Env
  {
  private:
    Persistent<Context> context;
    Handle<Object> Global();
    void Setup();
  public:
    Env();
    ~Env();
    Script* Eval(string src, string fname="<eval>");
  };
}

#define MIKE_SET(obj, name, assignee) \
  obj->Set(v8::String::NewSymbol(name), assignee)

#define MIKE_SET_GLOBAL(name, assignee)	\
  MIKE_SET(Global(), name, assignee)

#define MIKE_SET_METHOD(obj, name, callback) \
  MIKE_SET(obj, name, v8::FunctionTemplate::New(callback)->GetFunction())

#endif /* _MIKE_ENV_H_ */
