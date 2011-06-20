#ifndef _MIKE_XML_ELEMENT_H_
#define _MIKE_XML_ELEMENT_H_

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <string>

namespace mike
{
  using namespace std;
  
  class XmlElement
  {
  public:
    /**
     * Constructor.
     *
     */
    explicit XmlElement(xmlNode* node);

    /**
     * Destructor.
     *
     */
    virtual ~XmlElement();
    
  protected:
    xmlNode* node_;
  };
}

#endif /* _MIKE_XML_ELEMENT_H_ */
