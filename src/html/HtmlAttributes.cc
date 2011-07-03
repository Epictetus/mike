#include <stdarg.h>
#include "html/HtmlAttributes.h"
#include "utils/Helpers.h"

namespace mike
{
  /////////////////////////////// PUBLIC ///////////////////////////////////////

  //============================= ACCESS     ===================================
  
  string HtmlElementWithCoreAttrs::getClass()
  {
    return self()->getAttribute("class");
  }
  
  vector<string> HtmlElementWithCoreAttrs::getClasses()
  {
    if (hasClass())
      return strsplit(getClass());
    else
      return vector<string>();
  }

  bool HtmlElementWithCoreAttrs::hasClass()
  {
    return self()->hasAttribute("class");
  }
  
  bool HtmlElementWithCoreAttrs::hasClass(string klass)
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

  bool HtmlElementWithCoreAttrs::hasClasses(int n_args, ...)
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

  bool HtmlElementWithCoreAttrs::hasAnyClass(int n_args, ...)
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
