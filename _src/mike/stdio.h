#ifndef _MIKE_STDIO_H_
#define _MIKE_STDIO_H_

#include <stdio.h>
#include "mike.h"
#include "mike/script.h"

namespace mike {
  namespace stdio
  {
    using namespace v8;
    
    Handle<Value> WriteStdout(const Arguments &args);
    Handle<Value> WriteStderr(const Arguments &args);
    Handle<Value> LoadFile(const Arguments &args);
    Handle<Value> ReadFile(const Arguments &args);
  }
}

#endif /* _MIKE_STDIO_H_ */
