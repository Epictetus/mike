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

  Handle<Object> Env::Global()
  {
    return context->Global();
  }
  
  void Env::Setup()
  {
    HandleScope scope;

    // $stdout
    Handle<Object> o_stdout(Object::New());
    MIKE_SET_METHOD(o_stdout, "write", stdio::WriteStdout);
    MIKE_SET_GLOBAL("$stdout", o_stdout);
    
    // $stderr
    Handle<Object> o_stderr(Object::New());
    MIKE_SET_METHOD(o_stderr, "write", stdio::WriteStderr);
    MIKE_SET_GLOBAL("$stderr", o_stderr);
    
    // $file
    Handle<Object> o_file(Object::New());
    MIKE_SET_METHOD(o_file, "load", stdio::LoadFile);
    MIKE_SET_METHOD(o_file, "read", stdio::ReadFile);
    MIKE_SET_GLOBAL("$file", o_file);

    // $uri
    Handle<Object> o_uri(Object::New());
    MIKE_SET_METHOD(o_uri, "open", net::Open);
    MIKE_SET_GLOBAL("$uri", o_uri);

    // $thread
    //Handle<Object> o_thread(Object::New());
    //MIKE_SET_METHOD(o_thread, "tick", thread::Tick);
    //MIKE_SET_METHOD(o_thread, "spawn", thread::Spawn);
    //MIKE_SET_METHOD(o_thread, "sleep", thread::Sleep);
    //MIKE_SET_GLOBAL("$thread", o_thread);
  }
}
