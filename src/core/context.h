#ifndef _MIKE_CORE_CONTEXT_H_
#define _MIKE_CORE_CONTEXT_H_

#include <stdlib.h>
#include <string>
#include <list>
#include <v8.h>

#include "core/script.h"
#include "glue/glue.h"

namespace mike {
  namespace context
  {
    using namespace v8;
    using namespace std;

    class Window;
    Window* New();

    /*
     * This class encapsulates base v8 context extended by mike's standard
     * libarary and browser stuff, and of course provides api for evaluating
     * javascript within. 
     *
     */
    class Window
    {
    protected:
      list<script::Info*> results;
      Persistent<Context> context;
      Persistent<Array> loadPath;
    public:
      Window();
      ~Window();
      Handle<Array> LoadPath();
      void EnterContext();
      script::Info* LastExecutedScript();
      script::Info* Evaluate(string src, string fname = "<eval>");
    };
  }
}

#endif /* _MIKE_CORE_CONTEXT_H_ */
