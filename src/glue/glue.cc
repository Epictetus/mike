#include "glue/glue.h"
#include "glue/file.h"
#include "glue/system.h"
#include "glue/stdio.h"

namespace mike {
  namespace glue
  {
    using namespace std;
    using namespace v8;

    /*
     * Registers whole stuff provided by native code within given context. 
     *
     */
    void Splice(Handle<Context> context)
    {
      HandleScope scope;
      Handle<Object> global = context->Global();

      // Global objects
      global->Set(String::NewSymbol("Stdout"), StdoutObject());
      global->Set(String::NewSymbol("Stderr"), StderrObject());
      global->Set(String::NewSymbol("File"), FileObject());
      global->Set(String::NewSymbol("System"), SystemObject());

      // Load path
      Handle<Array> loadpath(Array::New());
      loadpath->Set(0, String::New(MIKE_LIB_DIR));
      global->Set(String::NewSymbol("$LOAD_PATH"), loadpath);
    }
  }
}
