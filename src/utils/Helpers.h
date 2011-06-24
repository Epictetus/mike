#ifndef _MIKE_HELPERS_H_
#define _MIKE_HELPERS_H_

#include <string>

namespace mike
{
  using namespace std;
  
  /**
   * Strips all leading and trailing whitespaces from given string.
   *
   */
  char* strstrip(string value);

  /**
   * Sanitizes given XPath argument.
   *
   */
  string xpathSanitize(string arg);
}

#endif /* _MIKE_HELPERS_H_ */
