#include <string.h>
#include <stdlib.h>
#include "xml/XmlPage.h"
#include "utils/Helpers.h"

namespace mike
{
  /////////////////////////////// HELPERS //////////////////////////////////////

  void xmlErrorHandler(void *ctx, const char *msg, ...)
  {
    // so far nothing, just mute errors...
  }

  xmlXPathObjectPtr findByXPath(xmlDocPtr doc, string xpath)
  {
    if (doc) {
      // Setup XPath stuff and evaluate expression
      xmlChar* cxpath = xmlCharStrdup(xpath.c_str());
      xmlXPathContextPtr ctx = xmlXPathNewContext(doc);
      xmlXPathObjectPtr found = xmlXPathEvalExpression(cxpath, ctx);

      // Free XPath stuff
      xmlXPathFreeContext(ctx);
      xmlFree(cxpath);

      // Return results if any
      if (found == NULL) {
	throw InvalidXpathExpressionError(xpath);
      } else if (!xmlXPathNodeSetIsEmpty(found->nodesetval)) {
	return found;
      } else {
	xmlXPathFreeObject(found);
      }
    }
      
    return NULL;
  }

  int normalizePathLevel(string *level)
  {
    int split = (*level).find('[');

    if (split > 0) {
      string pos = (*level).substr(split+1);
      *level = (*level).substr(0, split);
      
      if ((split = pos.find(']')) > 0) {
	pos = pos.substr(0, split);
	return atoi(pos.c_str());
      } else {
	return 0;
      }
    };

    return 1;
  }

  /////////////////////////////// PUBLIC ///////////////////////////////////////
  
  //============================= LIFECYCLE ====================================
  
  XmlPage::XmlPage(Request* request)
    : Page(request, kXmlPage)
  {
    doc_ = NULL;
    prepareDocument();
  }

  XmlPage::~XmlPage()
  {
    cleanupDocument();
  }

  //============================= ACCESS     ===================================
  
  vector<XmlElement*> XmlPage::getElementsByXpath(string xpath)
  {
    vector<XmlElement*> result;
    xmlXPathObjectPtr found = findByXPath(doc_, xpath);

    if (found) {
      xmlNodeSetPtr nodeset = found->nodesetval;
      XmlElement* elements[nodeset->nodeNr];
	
      for (int i = 0; i < nodeset->nodeNr; i++) {
	elements[i] = newElement(nodeset->nodeTab[i]);
	usedElements_.push_back(elements[i]);
      }
      
      result.assign(elements, elements+nodeset->nodeNr);
      xmlXPathFreeObject(found);
    }
      
    return result;
  }
  
  XmlElement* XmlPage::getElementByXpath(string xpath)
  {
    xmlXPathObjectPtr found = findByXPath(doc_, xpath);
    
    if (found) {
      XmlElement* elem = newElement(found->nodesetval->nodeTab[0]);
      xmlXPathFreeObject(found);
      usedElements_.push_back(elem);
      return elem;
    } else {
      throw ElementNotFoundError("XPath = " + xpath);
    }
  }

  XmlElement* XmlPage::getElementByPath(string path)
  {
    if (doc_ && !path.empty()) {
      vector<string> levels = strsplit(path, '/');
      xmlNodePtr node = NULL;

      for (vector<string>::iterator it = levels.begin(); it != levels.end(); it++) {
	string level = *it;
	int pos = normalizePathLevel(&level);

	if (pos == 0) {
	  node = NULL;
	  break;
	}
	
	node = node ? node->children : doc_->children;
	
	while (node) {
	  if (strcmp((char*)node->name, level.c_str()) == 0 && --pos == 0) {
	    break;
	  } else {
	    node = node->next;
	  }
	}

	if (node == NULL)
	  break;
      }

      if (node) {
	XmlElement* elem = newElement(node);
	usedElements_.push_back(elem);
	return elem;
      }
    }

    throw ElementNotFoundError("Path = " + path);
  }
  
  vector<XmlElement*> XmlPage::getElementsByTagName(string tag)
  {
    vector<XmlElement*> result;
      
    if (doc_ && !tag.empty()) {
      getElementsByTagNameIter(tag, doc_->children, &result);
    }

    return result;
  }

  //============================= OPERATIONS ===================================
  
  void XmlPage::reload()
  {
    Page::reload();
    prepareDocument();
  }

  /////////////////////////////// PROTECTED  ///////////////////////////////////
  
  void XmlPage::prepareDocument()
  {
    cleanupDocument();
    parseDocument();
  }

  void XmlPage::parseDocument()
  {
    xmlSetGenericErrorFunc((void*)this, xmlErrorHandler);
    xmlChar* body = xmlCharStrdup(getResponse()->getBody().c_str());

    // FIXME: encoding should be taken from http response!
    doc_ = xmlReadDoc(body, getUrl().c_str(), "utf-8",
		      XML_PARSE_RECOVER | XML_PARSE_NOERROR | XML_PARSE_NOWARNING);

    xmlFree(body);
  }
  
  void XmlPage::cleanupDocument()
  {
    if (doc_ != NULL) {
      xmlFreeDoc(doc_);
      doc_ = NULL;
      delete_all< list<XmlElement*> >(&usedElements_);
    }
  }

  void XmlPage::getElementsByTagNameIter(string tag, xmlNodePtr node, vector<XmlElement*>* elems)
  {
    while (node) {
      if (node->name && (strcmp((char*)node->name, tag.c_str()) == 0)) {
	XmlElement* elem = newElement(node);
	usedElements_.push_back(elem);
	elems->push_back(elem);
      }
	
      getElementsByTagNameIter(tag, node->children, elems);
      node = node->next;
    }
  }

  XmlElement* XmlPage::newElement(xmlNodePtr node)
  {
    return new XmlElement(this, node);
  }
}
