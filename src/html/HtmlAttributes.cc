#include <stdarg.h>
#include "html/HtmlAttributes.h"
#include "utils/Helpers.h"

namespace mike
{
  string HtmlCoreAttrs::getClass()
  {
    return getAttribute("class");
  }
  
  vector<string> HtmlCoreAttrs::getClasses()
  {
    return strsplit(getClass());
  }

  bool HtmlCoreAttrs::hasClass()
  {
    return hasAttribute("class");
  }
  
  bool HtmlCoreAttrs::hasClass(string klass)
  {
    vector<string> classes = getClasses();
    
    for (vector<string>::iterator it = classes.begin(); it != classes.end(); it++) {
      if (*it == klass)
	return true;
    }

    return false;
  }

  bool HtmlCoreAttrs::hasClasses(int n_args, ...)
  {
    va_list args;
    va_start(args, n_args);

    for (int i = 0; i < n_args; i++) {
      if (!hasClass(string(va_arg(args, char*))))
	return false;
    }

    return true;
  }

  bool HtmlCoreAttrs::hasAnyClass(int n_args, ...)
  {
    va_list args;
    va_start(args, n_args);

    for (int i = 0; i < n_args; i++) {
      if (hasClass(string(va_arg(args, char*))))
	return true;
    }

    return false;
  }
}
