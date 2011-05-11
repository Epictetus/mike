#include "lib/glue/glue.h"
#include "lib/glue/file.h"
#include "lib/glue/system.h"

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

      global->Set(String::NewSymbol("File"), FileObject());
      global->Set(String::NewSymbol("System"), SystemObject());
    }
  }
}
