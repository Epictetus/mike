#include "xml/XmlElementSet.h"

namespace mike
{
  XmlElementSet::XmlElementSet()
  {
  }
  
  XmlElementSet::XmlElementSet(XmlElement* elements[], int size)
  {
    assign(size, elements);
  }

  XmlElementSet::~XmlElementSet()
  {
    clear();
  }

  void XmlElementSet::assign(int size, XmlElement* elements[])
  {
    elements_.assign(elements, elements + size);
  }

  int XmlElementSet::size()
  {
    return elements_.size();
  }
    
  void XmlElementSet::clear()
  {
    for (vector<XmlElement*>::iterator it = begin(); it != end(); it++)
      delete *it;

    elements_.clear();
  }

  bool XmlElementSet::empty()
  {
    return elements_.empty();
  }

  vector<XmlElement*>::iterator XmlElementSet::begin()
  {
    return elements_.begin();
  }

  vector<XmlElement*>::iterator XmlElementSet::end()
  {
    return elements_.end();
  }

  XmlElement* XmlElementSet::front()
  {
    return elements_.front();
  }

  XmlElement* XmlElementSet::back()
  {
    return elements_.back();
  }

  void XmlElementSet::push_back(XmlElement* elem)
  {
    elements_.push_back(elem);
  }
  
  void XmlElementSet::pop_back()
  {
    elements_.pop_back();
  }

  XmlElement* XmlElementSet::operator[](int n)
  {
    return elements_[n];
  }
}
