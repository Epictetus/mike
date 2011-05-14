#ifndef _MIKE_LIB_FILE_H_
#define _MIKE_LIB_FILE_H_

#include <sys/types.h>
#include "glue/glue.h"

namespace mike {
  namespace glue {
    namespace file
    {
      bool exists_p(string fname);
      bool check_st_mode(string fname, int mode);
      bool read_contents(string *content, string fname);
    }
    
    Handle<Object> FileObject();
  }
}

#endif /* _MIKE_LIB_FILE_H_ */
