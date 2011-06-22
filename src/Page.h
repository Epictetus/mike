#ifndef _MIKE_PAGE_H_
#define _MIKE_PAGE_H_

#include <string>
#include "http/Request.h"

namespace mike
{
  using namespace std;
  using namespace http;

  class RegularPage;
  class XmlPage;
  class HtmlPage;
  
  /**
   * Available page types. 
   *
   */
  enum PageType {
    UNKNOWN_PAGE,
    XML_PAGE,
    HTML_PAGE,
    REGULAR_PAGE
  };
  
  /**
   * Object of this class represents single page loaded by corresponding request.
   * This is base class for all complex kinds of pages, like HTML, XML, Text page, etc.
   *
   */
  class Page
  {
  public:
    /**
     * Performs given request, and depending on response content type build proper
     * page object for it. Example: 
     *
     * <code>
     *   http::Request* req = http::Request::Get("http://www.mikebrowser.com/");
     *   Page* page = Page::Build(req);
     *   // ...
     *   delete page;
     * </code>
     *
     * Note: you don't need to delete req object, it will be done automatically on page destroy.
     *
     */
    static Page* Build(Request* request);

    /**
     * Constructor.
     *
     */
    explicit Page(Request* request, PageType type);
    
    /**
     * Destructor.
     *
     */
    virtual ~Page();

    /**
     * Returns HTTP request built for this page.
     *
     */
    Request* getRequest();

    /**
     * Returns HTTP response built for this page.
     *
     */
    Response* getResponse();

    /**
     * Requrns request url of this website.
     *
     */
    string getUrl();
    
    /**
     * Returns <code>true</code> when current page is an XML or HTML page.
     *
     */
    bool isXml();

    /**
     * Returns <code>true</code> when current page is an HTML page.
     *
     */
    bool isHtml();

    /**
     * Returns <code>true</code> when current page is an regular file.
     *
     */
    bool isRegular();

    /**
     * If current page is an XML (or HTML) document then returns <code>XmlPage</code>
     * object, otherwise <code>NULL</code> will be returned.
     *
     */
    XmlPage* toXmlPage();

    /**
     * If current page is an HTML document then returns <code>HtmlPage</code>
     * object, otherwise <code>NULL</code> will be returned.
     *
     */
    HtmlPage* toHtmlPage();

    /**
     * If current page is an regular file then returns <code>RegularPage</code> object
     * representing it, otherwise <code>NULL</code> will be returned.
     *
     */
    RegularPage* toRegularPage();

    /**
     * Returns <code>true</code> when page has been properly loaded.
     *
     */
    virtual bool isLoaded();
    
    /**
     * Performs request to this page once again and reloads everything.
     *
     */
    virtual void reload();
    
  protected:
    http::Request* request_;
    PageType type_;
  };
}

#endif /* _MIKE_PAGE_H_ */
