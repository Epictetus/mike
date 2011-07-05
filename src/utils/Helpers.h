#ifndef _MIKE_HELPERS_H_
#define _MIKE_HELPERS_H_

#include <string>
#include <vector>
#include <list>

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
   * Combines given array of strings, optionally using specified separator.
   *
   * \param parts Strings to combine.
   * \param size Number of strings to join.
   * \param separator Separator placed between joined strings.
   * \return Combined string.
   */
  string strjoin(string parts[], int size, string separator="");

  /**
   * Splits given string by given delimiter into vector of substrings.
   *
   * \param text Text to split.
   * \param delim Delimiter.
   * \return Vector of substrings.
   */
  vector<string> strsplit(string text, char delim=' ');
  
  /**
   * Sanitizes given XPath argument.
   *
   * \param arg Argument to sanitize.
   * \return Sanitized XPath argument.
   */
  string xpathSanitize(string arg);

  /**
   * Returns true when given string element is included in specified array.
   *
   * \param elem Searched element.
   * \param opts Array with possible options.
   * \param numopts Given array's size.
   * \return Whether given element is included in the array or not.
   */
  bool isIncluded(string elem, string opts[], int numopts);
      
  /**
   * Deletes all pointers in given vector and clears it out.
   *
   * \code
   *   vector<HtmlElement*> elems;
   *   elems.push_back(elem1);
   *   //...
   *   delete_all< vector<HtmlElement*> >(&elems);
   * \endcode
   *
   * \param elems Vector of pointers.
   */
  template <typename T> void delete_all(T* c)
  {
    for (typename T::iterator it = c->begin(); it != c->end(); it++) {
      delete *it;
      *it = NULL;
    }
    
    c->clear();
  }

  // TODO: figure out if there is easier way to cast vector of pointers...
  /**
   * Casts all pointers from given vector to specified type.
   *
   * \code
   *   vector<Derived> elems(new Derived(1), new Derived(2));
   *   vector<Base> base_elems = vector_cast<Derived,Base>(elems);
   * \endcode
   *
   * \param v Input vector.
   * \return Converted vector.
   */
  template <typename F, typename T> vector<T*> vector_cast(vector<F*> v)
  {
    vector<T*> result;
    result.resize(v.size());
    int i = 0;
    
    for (typename vector<F*>::iterator it = v.begin(); it != v.end(); it++)
      result[i++] = (T*)*it;

    return result;
  }
}

#endif /* _MIKE_HELPERS_H_ */
