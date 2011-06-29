#ifndef _MIKE_HELPERS_H_
#define _MIKE_HELPERS_H_

#include <string>

namespace mike
{
  using namespace std;
  
  /**
   * Strips all leading and trailing whitespaces from given string.
   *
   * \param value Text to strip whitespaces.
   * \return Text without leading and trailing whitespaces.
   */
  char* strstrip(string value);

  /**
   * Sanitizes given XPath argument.
   *
   * \param arg Argument to sanitize.
   * \return Sanitized XPath argument.
   */
  string xpathSanitize(string arg);
}

#endif /* _MIKE_HELPERS_H_ */
