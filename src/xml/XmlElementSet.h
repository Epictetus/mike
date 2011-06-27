#ifndef _MIKE_XML_ELEMENT_SET_
#define _MIKE_XML_ELEMENT_SET_

#include <string>
#include <vector>
#include "xml/XmlElement.h"

namespace mike
{
  /**
   * Container for <code>XmlElement</code> objects built at top of STL <code>vector</code>.
   *
   * Examples:
   *
   * <code>
   *   XmlElementSet set(array_of_nodes, 10);
   *   set.push_back(new XmlElement(page, node));
   *   XmlElement* some_node = set[2];
   *   // ...
   *   set.clear();
   * </code>
   *
   */
  class XmlElementSet
  {
  public:
    /**
     * Constructors.
     *
     */
    explicit XmlElementSet();
    explicit XmlElementSet(XmlElement* elements[], int size);

    /**
     * Destructor.
     *
     */
    virtual ~XmlElementSet();

    /**
     * See STL <code>vector::clear</code>.
     *
     */
    void assign(int size, XmlElement* elements[]);

    /**
     * See STL <code>vector::size</code>.
     *
     */
    int size();
    
    /**
     * See STL <code>vector::clear</code>.
     *
     */
    void clear();

    /**
     * See STL <code>vector::empty</code>.
     *
     */
    bool empty();

    /**
     * See STL <code>vector::begin</code>.
     *
     */
    vector<XmlElement*>::iterator begin();

    /**
     * See STL <code>vector::end</code>.
     *
     */
    vector<XmlElement*>::iterator end();

    /**
     * See STL <code>vector::front</code>.
     *
     */
    XmlElement* front();

    /**
     * See STL <code>vector::back</code>.
     *
     */
    XmlElement* back();

    /**
     * See STL <code>vector::push_back</code>.
     *
     */
    void push_back(XmlElement* elem);

    /**
     * See STL <code>vector::pop_back</code>.
     *
     */
    void pop_back();

    /**
     * See STL <code>vector::operator[]</code>.
     *
     */
    XmlElement* operator[](int n);

  protected:
    vector<XmlElement*> elements_;
  };
}

#endif /* _MIKE_XML_ELEMENT_SET_ */
