#include <stdarg.h>
#include "html/HtmlAttrs.h"
#include "utils/Helpers.h"

namespace mike
{
  /////////////////////////////// PUBLIC ///////////////////////////////////////
  
  //============================= ACCESS     ===================================
  
  string HtmlCoreAttrs::getClass()
  {
    return self()->getAttribute("class");
  }
  
  vector<string> HtmlCoreAttrs::getClasses()
  {
    if (hasClass())
      return strsplit(getClass());
    else
      return vector<string>();
  }

  bool HtmlCoreAttrs::hasClass()
  {
    return self()->hasAttribute("class");
  }
  
  bool HtmlCoreAttrs::hasClass(string klass)
  {
    if (hasClass()) {
      vector<string> classes = getClasses();
      
      for (vector<string>::iterator it = classes.begin(); it != classes.end(); it++) {
	if (*it == klass)
	  return true;
      }
    }
    
    return false;
  }

  bool HtmlCoreAttrs::hasClasses(int n_args, ...)
  {
    if (hasClass()) {
      va_list args;
      va_start(args, n_args);

      for (int i = 0; i < n_args; i++) {
	if (!hasClass(string(va_arg(args, char*))))
	  return false;
      }
    }

    return true;
  }

  bool HtmlCoreAttrs::hasAnyClass(int n_args, ...)
  {
    if (hasClass()) {
      va_list args;
      va_start(args, n_args);
      
      for (int i = 0; i < n_args; i++) {
	if (hasClass(string(va_arg(args, char*))))
	  return true;
      }
    }

    return false;
  }
}
