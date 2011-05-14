#ifndef _MIKE_CORE_CONTEXT_H_
#define _MIKE_CORE_CONTEXT_H_

#include <stdlib.h>
#include <string>
#include <list>
#include <v8.h>

#define MIKE_LIB_DIR DATADIR + "/mike/site-javascript"

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
      Persistent<Context> context;
      void SpliceRequire();
      void EnterContext();
    public:
      Window();
      ~Window();
      Handle<Value> Require(string module);
      Handle<Array> LoadPath();
      Handle<Value> Evaluate(string src, string fname = "<eval>");
    };
  }
}

#endif /* _MIKE_CORE_CONTEXT_H_ */
