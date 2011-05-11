#ifndef _MIKE_GLUE_SYSTEM_H_
#define _MIKE_GLUE_SYSTEM_H_

#include "lib/glue/glue.h"

namespace mike {
  namespace glue {
    namespace system
    {
      using namespace std;
      using namespace v8;
      
      Handle<Value> pwd(const Arguments &args); // pwd() -> String
      Handle<Value> cwd(const Arguments &args); // cwd(path) -> Boolean
    }

    Handle<Object> SystemObject();
  }
}


#endif /* _MIKE_GLUE_SYSTEM_H_ */
