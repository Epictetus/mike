#ifndef _MIKE_PECTOR_H_
#define _MIKE_PECTOR_H_

#include <vector>
#include <string>
#include "utils/Helpers.h"

namespace mike
{
  using namespace std;
  
  /**
   * Pector is an vector of pointers with auto deleting containing elements
   * when its destructor is called. It provides some features of normal STL vector
   * struct - see its docs for details.
   *
   * \code
   *   pector<XmlElement> pv = pector<XmlElement>();
   *   pv.push_back(first_elem);
   *   pv.push_back(second_elem);
   *   assert(pector.size(), 2);
   *   assert(pector[0], first_elem);
   *   //...
   * \endcode
   */
  template <typename T> class pector
  {
  public:
    typedef typename vector<T*>::iterator iterator;
    
    /**
     * Creates empty instance.
     */
    pector()
    {
    }

    /**
     * Creates new instance with initial set of items.
     *
     * \param items Initial items array.
     * \param size Size of initial items.
     */
    pector(T* items[], int size)
    {    
      assign(size, items);
    }

    /**
     * Destructor.
     */
    ~pector()
    {
    }

    void assign(int size, T* items[])
    {
      items_.assign(items, items + size);
    }

    int size()
    {
      return items_.size();
    }
    
    void clear()
    {
      delete_all< vector<T*> >(&items_);
    }

    bool empty()
    {
      return items_.empty();
    }

    iterator begin()
    {
      return items_.begin();
    }

    iterator end()
    {
      return items_.end();
    }

    void push_back(T* item)
    {
      items_.push_back(item);
    }
  
    void pop_back()
    {
      T* p = NULL;
      swap(p, items_[items_.size()-1]);
      delete p;
      items_.pop_back();
    }

    T* front()
    {
      return items_.front();
    }

    T* back()
    {
      return items_.back();
    }

    T* get(int n)
    {
      return (T*)items_[n];
    }

    T* at(int n)
    {
      return (T*)items_[n];
    }
    
    T* operator[](int n)
    {
      return (T*)items_[n];
    }

    /**
     * Picks up specified pointer and removes its reference from the container. Remember,
     * that you have to delete returned value on your own, it will be not removed by this
     * Pector.
     *
     * \code
     *   Pector<XmlElement>* pv = new Pector<XmlElement>(elems, 10);
     *   XmlElement* elem = pv->pick(5);
     *   delete pv;
     *   // elem is still available here so have to be removed...
     *   delete elem;
     * \endcode
     *
     * \param n Index of pointer to pick up.
     * \return Pointer from specified index.
     */
    T* pick(int n)
    {
      T* p = NULL;
      swap(p, items_[n]);
      iterator it = (iterator)items_.begin();
      advance(it, n);
      items_.erase(it);
      return p;
    }

  protected:
    vector<T*> items_;
  };
}

#endif /* _MIKE_PECTOR_H_ */
