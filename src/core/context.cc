#include "core/context.h"

namespace mike {
  namespace context
  {
    using namespace v8;
    using namespace std;

    /*
     * Creates and returns new Window context.
     *
     */
    Window* New()
    {
      return new Window();
    }
    
    Window::Window()
    {
      HandleScope scope;
      context = v8::Context::New();
      context->Enter();
      glue::Splice(context);
    }

    Window::~Window()
    {
      for (list<script::Info*>::iterator it = results.begin(); it != results.end(); it++) {
	delete *it;
      }
      
      context.Dispose();
    }

    /*
     * Enters into v8 context if necessary. If context is already entered it
     * does nothing. 
     *
     */
    void Window::EnterContext()
    {
      if (!Context::InContext() || Context::GetEntered() != context) {
	context->Enter();
      }
    }

    /*
     * Evaluates given javascript source within global window context and
     * returns <code>mike::script::Info</code> struct with result and info. 
     * 
     *   mike::context::Window *window = mike::context::New();
     *   window->Evaluate("var a=1;");
     *   window->Evaluate("var b=a+1;");
     *   delete window;
     *
     */
    script::Info* Window::Evaluate(string src, string fname/*= "<eval>"*/)
    {
      HandleScope scope;
      EnterContext();
      script::Info* info = script::Run(src, fname);
      results.push_back(info);
      return info;
    }

    /*
     * Returns <code>script::Info</code> object for the last executed script.
     *
     */
    script::Info* Window::LastExecutedScript()
    {
      if (results.empty()) {
	return NULL;
      } else {
	return results.back();
      }
    }
  }
}
