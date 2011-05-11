#ifndef _MIKE_LIB_FILE_H_
#define _MIKE_LIB_FILE_H_

#include "glue/glue.h"

namespace mike {
  namespace glue {
    namespace file
    {
      bool exists_p(string fname);
      bool check_st_mode(string fname, int mode);
      char* read_contents(char *fname);
    }
    
    Handle<Object> FileObject();
  }
}

#endif /* _MIKE_LIB_FILE_H_ */
