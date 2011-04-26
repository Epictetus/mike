#include "mike/env.h"

namespace mike
{
  using namespace v8;
  using namespace std;
  
  Env::Env()
  {
    HandleScope scope;
    context = v8::Context::New();
    context->Enter();
    Setup();
  }

  Env::~Env()
  {
    if (v8::Context::InContext() && v8::Context::GetEntered() == context) {
      context->Exit();
    }
    context.Dispose();
  }

  // Public

  Script* Env::Eval(string src, string fname/*="<eval>"*/)
  {
    HandleScope scope;
    
    if (!Context::InContext() || Context::GetEntered() != context) {
      context->Enter();
    }

    Script *script = Script::Run(src, fname);
    return script;
  }
  
  // Private
  
  void Env::Setup()
  {
    HandleScope scope;

    // $stdout
    MIKE_OBJ(mike_stdout);
    MIKE_SET_METHOD(mike_stdout, "write", stdio::WriteStdout);
    MIKE_SET(context->Global(), "$stdout", mike_stdout);
    
    // $stderr
    MIKE_OBJ(mike_stderr);
    MIKE_SET_METHOD(mike_stderr, "write", stdio::WriteStderr);
    MIKE_SET(context->Global(), "$stderr", mike_stderr);
    
    // $io
    MIKE_OBJ(mike_file);
    MIKE_SET_METHOD(mike_file, "read", stdio::ReadFile);
    MIKE_SET(context->Global(), "$io", mike_file);

    // $net
    //MIKE_OBJ(mike_net);
    //MIKE_SET_METHOD(mike_net, "open", net::Open);
    //MIKE_SET(context->Global(), "$net", mike_net);

    // $thread
    //MIKE_OBJ(mike_file);
    //MIKE_SET_METHOD(mike_thread, "tick", thread::Tick);
    //MIKE_SET_METHOD(mike_thread, "spawn", thread::Spawn);
    //MIKE_SET_METHOD(mike_thread, "sleep", thread::Sleep);
    //MIKE_SET(context->Global(), "$thread", mike_thread);
  }
}
