#ifndef _MIKE_GLUE_IO_H_
#define _MIKE_GLUE_IO_H_

#include <stdio.h>
#include <string>
#include "glue/glue.h"

namespace mike {
  namespace glue
  {
    Handle<Object> StdoutObject();
    Handle<Object> StderrObject();
  }
}

#endif /* _MIKE_GLUE_IO_H_ */
