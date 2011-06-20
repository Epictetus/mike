#ifndef _MIKE_XML_ELEMENT_H_
#define _MIKE_XML_ELEMENT_H_

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <string>

namespace mike
{
  using namespace std;

  class XmlPage;

  /**
   * This class represents single XML node element. It wraps up libxml2's <code>xmlNode</code>
   * and provides some extra functionalities at top of it.
   *
   */
  class XmlElement
  {
  public:
    /**
     * Constructor.
     *
     */
    explicit XmlElement(XmlPage* page, xmlNode* node);

    /**
     * Destructor.
     *
     */
    virtual ~XmlElement();
    
  protected:
    XmlPage* page_;
    xmlNode* node_;
  };
}

#endif /* _MIKE_XML_ELEMENT_H_ */
