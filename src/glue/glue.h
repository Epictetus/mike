#ifndef _MIKE_LIB_GLUE_H_
#define _MIKE_LIB_GLUE_H_

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <v8.h>

#include "core/context.h"

#ifndef MIKE_LIBDIR
#define MIKE_LIBDIR DATADIR "/mike/site-javascript"
#endif

namespace mike {
  namespace glue
  {
    using namespace std;
    using namespace v8;

    void Splice(context::Window *window, Handle<Object> global);
  }
}

#endif /* _MIKE_LIB_GLUE_H_ */
