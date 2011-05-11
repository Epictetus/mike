#ifndef _MIKE_LIB_GLUE_H_
#define _MIKE_LIB_GLUE_H_

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <v8.h>

namespace mike {
  namespace glue
  {
    using namespace std;
    using namespace v8;

    void Splice(Handle<Context> context);
  }
}

#endif /* _MIKE_LIB_GLUE_H_ */
