#ifndef _MIKE_GLUE_IO_H_
#define _MIKE_GLUE_IO_H_

#include <stdio.h>
#include <string>
#include "glue/glue.h"

namespace mike {
  namespace glue {
    namespace io
    {
      using namespace std;
      using namespace v8;
      
      Handle<Value> stdoutWrite(const Arguments &args); // $stdout.write(text)
      Handle<Value> stderrWrite(const Arguments &args); // $stderr.write(text)
    }

    Handle<Object> StdoutObject();
    Handle<Object> StderrObject();
  }
}

#endif /* _MIKE_GLUE_IO_H_ */
