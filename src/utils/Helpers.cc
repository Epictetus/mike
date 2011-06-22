#include "utils/Helpers.h"

namespace mike
{
  char *strstrip(string value)
  {
    char* s = (char*)value.c_str();
    size_t size = strlen(s);
    
    if (!size) {
      return s;
    }
    
    char *end = s + size -1;
    
    while (end >= s && isspace(*end)) {
      end--;
    }
    
    *(end + 1) = '\0';
    
    while (*s && isspace(*s)) {
      s++;
    }
    
    return s;
  }
}
